TABLE_(TASK)
	SERIAL_		(ID) PRIMARY_KEY
	STRING_ 	(TITLE, 1024) INDEX
	LONG_		(DESCRIPTION)
	TIME_ 		(CREATED)
	INT_		(DONE) INDEX SQLDEFAULT(0)
	STRING_		(PROJECT, 256) INDEX // TODO: use PROJECT_ID and REFERENCE to the PROJECT TABLE
END_TABLE