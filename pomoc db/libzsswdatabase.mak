vpath_src=. ..
vpath_header=. ..
vpath #tu jest spacja
LIBS=arch src
LD_EXTRA_FLAGS=$(TEST) -ggdb -pthread `pkg-config QtCore QtTest QtSql QtGui --libs` -Wl,--no-gc-sections -lstdc++ -L. -L../lib -Llib -lsrc -larch -lzsswdatabase
C_EXTRA_FLAGS=$(TEST) -Wall -W `pkg-config QtCore QtTest QtSql QtGui --cflags` -pthread -I./src
MAIN_TARGET=test
PROJECT_ITEMS= src/test/CAbstractDatabaseTest.cc \
        src/test/CDatabaseArgumentParser.cc \
        src/test/CDatabaseArgumentParserTest.cc \
        src/test/CDatabaseConnectionMock.cc \
        src/test/CDatabaseConnectionTest.cc \
        src/test/CDatabaseConnectionWrapper.cc \
        src/test/CDatabaseManagerTest.cc \
        src/test/CDatabaseTranslatorMock.cc \
        src/test/CDatabaseTranslatorTest.cc \
        src/test/CEmptyFilterTest.cc \
        src/test/CEqualFilterTest.cc \
        src/test/CEventsRepositoryTest.cc \
        src/test/CEventsRepositoryTestData.cc \
        src/test/CEventsRepositoryWrapper.cc \
        src/test/CEventsTypesRepositoryTest.cc \
        src/test/CGetNumberOfTurningOnTest.cc \
        src/test/CGetSimilarRecordTest.cc \
        src/test/CGetSummaryWorkTimeTest.cc \
        src/test/CQtTestArgumentParser.cc \
        src/test/CQtTestArgumentParserTest.cc \
        src/test/CRangeFilterTest.cc \
        src/test/CRecordsWithTimestampFromFutureTest.cc \
        src/test/CRepositoryMock.cc \
        src/test/CRepositoryTest.cc \
        src/test/CInsertingIntoRepositoryWithAdditionalTableTest.cc \
        src/test/CRepositoryWrapper.cc \
        src/test/CRepositoryWithAdditionalTableTest.cc \
        src/test/CShotsAndLrfMeasurementReportTest.cc \
        src/test/CSwitchingOfSwitchesQueriesTest.cc \
        src/test/CTemperatureReportTest.cc \
        src/test/CThereIsMatchingRecordTest.cc \
        src/test/moc_CDatabaseArgumentParserTest.cc \
        src/test/moc_CDatabaseConnectionTest.cc \
        src/test/moc_CDatabaseManagerTest.cc \
        src/test/moc_CDatabaseTranslatorMock.cc \
        src/test/moc_CDatabaseTranslatorTest.cc \
        src/test/moc_CEmptyFilterTest.cc \
        src/test/moc_CEqualFilterTest.cc \
        src/test/moc_CEventsRepositoryTest.cc \
        src/test/moc_CEventsRepositoryWrapper.cc \
        src/test/moc_CEventsTypesRepositoryTest.cc \
        src/test/moc_CGetNumberOfTurningOnTest.cc \
        src/test/moc_CGetSimilarRecordTest.cc \
        src/test/moc_CGetSummaryWorkTimeTest.cc \
        src/test/moc_CQtTestArgumentParserTest.cc \
        src/test/moc_CInsertingIntoRepositoryWithAdditionalTableTest.cc \
        src/test/moc_CRangeFilterTest.cc \
        src/test/moc_CRecordsWithTimestampFromFutureTest.cc \
        src/test/moc_CRepositoryTest.cc \
        src/test/moc_CRepositoryWrapper.cc \
        src/test/moc_CRepositoryWithAdditionalTableTest.cc \
        src/test/moc_CShotsAndLrfMeasurementReportTest.cc \
        src/test/moc_CTemperatureReportTest.cc \
        src/test/moc_CThereIsMatchingRecordTest.cc \
        src/test/moc_CSwitchingOfSwitchesQueriesTest.cc \
        src/test/TestMain.cc
