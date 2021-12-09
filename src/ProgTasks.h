#ifndef _ProgTasks_ProgTasks_h
#define _ProgTasks_ProgTasks_h

#include <CtrlLib/CtrlLib.h>
#include <SqlCtrl/SqlCtrl.h>
#include <PostgreSQL/PostgreSQL.h>
#include <CodeEditor/CodeEditor.h>

using namespace Upp;

#define LAYOUTFILE <ProgTasks/ProgTasks.lay>
#include <CtrlCore/lay.h>

struct ProgTasks : WithProgTasksLayout<TopWindow> {
	typedef ProgTasks CLASSNAME;
	ProgTasks();
	
	void InitTasksTable();
	void RefreshTasks();
	
	void HighlightCompletedTask(int row);
	void HighlightCompletedTasks();
	
	Vector<String> ListProjects();
	
	PostgreSQLSession pg_sess;
	EditString txtEditTitle, txtEditProject;
	Option editDone;
	EditTimeSpin editCreated;
};

#endif
