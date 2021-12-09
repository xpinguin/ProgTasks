#include "ProgTasks.h"

#define MODEL <ProgTasks/ProgTasks.sch>

#define SCHEMADIALECT <PostgreSQL/PostgreSQLSchema.h>
#include <Sql/sch_header.h>

#define SCHEMADIALECT <PostgreSQL/PostgreSQLSchema.h>
#include <Sql/sch_source.h>

#define SCHEMADIALECT <PostgreSQL/PostgreSQLSchema.h>
#include <Sql/sch_schema.h>


ProgTasks::ProgTasks() {
	CtrlLayout(*this, "ProgTasks DB");
	
	Add(tblTasks.HSizePos());
	Add(txtTitle.HSizePos());
	Add(txtDescription.HSizePos());
	Sizeable(true).SetMinSize(Null);
	
	btnRefresh << [=] () { RefreshTasks(); };
	
	tblTasks.WhenSel = [=] () {
		int row = tblTasks.GetCursor();
		if (row >= 0) {
			txtTitle <<= tblTasks.Get(row, 1);
		}
	};
	txtTitle << [=] () {
		int row = tblTasks.GetCursor();
		if (row >= 0) {
			tblTasks.Set(row, 1, txtTitle.GetData());
		}
	};
	txtEditTitle << [=] () {
		txtTitle <<= txtEditTitle.GetData();
	};
	
	tblTasks.WhenUpdateRow = [=] () { HighlightCompletedTask(tblTasks.GetCursor()); };
	tblTasks.WhenPostQuery = THISBACK(HighlightCompletedTasks);
	
	tblTasks.WhenFilter = [=] (const VectorMap<Id, Value> &row_values) -> bool {
		if (~cbHideCompleted && row_values[4]) return false;
		return true;
	};
	cbHideCompleted << [=] () { RefreshTasks(); };
	
	cmbProjectName << [=] () {
		String p = ~cmbProjectName;
		if (p.GetCharCount()) tblTasks.SetWhere(PROJECT == p);
		else tblTasks.SetWhere(TRUE);
		RefreshTasks();
	};
	
	txtDescription.LineNumbers(true);
	txtDescription.WordWrap(true);
}

void ProgTasks::InitTasksTable() {
	tblTasks.SetSession(pg_sess);
	///
	tblTasks.SetTable(TASK);
	tblTasks.AddKey(ID);
	tblTasks.AddColumn(TITLE, "Задача").Sorting().Edit(txtEditTitle);
	tblTasks.AddColumn(PROJECT, "Проект").Sorting().Edit(txtEditProject);
	tblTasks.AddColumn(CREATED, "Дата").Sorting()/*.Edit(editCreated)*/;
	tblTasks.AddColumn(DONE, "ОК").Sorting().SortDefault(false).Edit(editDone);
	tblTasks.AddCtrl(DESCRIPTION, txtDescription);
	tblTasks.ColumnWidths("436 60 35 30");
	///
	//tblTasks.Sort();
	RefreshTasks();
}

void ProgTasks::HighlightCompletedTasks() {
	HighlightCompletedTask(-1);
}

void ProgTasks::HighlightCompletedTask(int row) {
	auto &t = tblTasks;
	if (row > -1) {
		t.SetLineColor(row, t.Get(row, 4)?LtGreen():White());
	} else {
		for (int row = 0; row < t.GetCount(); row++) {
			t.SetLineColor(row, t.Get(row, 4)?LtGreen():White());
		}
	}
}

void ProgTasks::RefreshTasks() {
	tblTasks.SetOrderBy(Descending(ID), DONE);
	tblTasks.ReQuery();
	///
	{
		auto p = ~cmbProjectName;
		cmbProjectName.Clear();
		cmbProjectName.Add("");
		for (auto p : ListProjects()) {
			if (p.GetCharCount()) cmbProjectName.Add(p);
		}
		cmbProjectName.SetData(p);
	}
}

Vector<String> ProgTasks::ListProjects() {
	Vector<String> prjs;
	auto &sql = pg_sess.GetSessionSql();
	if (sql.Execute("SELECT DISTINCT project FROM task")) {
		while (sql.Fetch()) prjs.Add(sql[0]);
	}
	return prjs;
}

GUI_APP_MAIN {
	ProgTasks app;
	{
		auto &sess = app.pg_sess;
#ifdef _DEBUG
		sess.SetTrace();
#endif
		if (!sess.Open("host=localhost dbname=progtasks user=vns password=123456")) {
			Exclamation(Format("Error opening DB: %s", DeQtf(sess.GetLastError())));
			return;
		}
		{ // -- establish the schema
			SQL = sess;
			SqlSchema sch(PGSQL);
			
			All_Tables(sch);
			////
			Progress p;
			p.SetText("Creating ProgTasks database schema");
			if (/*true || */sch.ScriptChanged(SqlSchema::UPGRADE)) {
				SqlPerformScript(sch.Upgrade(), p);
			}
			if(sch.ScriptChanged(SqlSchema::ATTRIBUTES)) {
				SqlPerformScript(sch.Attributes(), p);
			}
			if(sch.ScriptChanged(SqlSchema::CONFIG)) {
				SqlPerformScript(sch.ConfigDrop(), p);
				SqlPerformScript(sch.Config(), p);
			}
			////
			sch.SaveNormal();
		}
		app.InitTasksTable();
	}
	app.Run();
}
