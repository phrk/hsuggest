

_CCFLAGS = '-c -Wall -D_REENTRANT -DHAVE_NETINET_IN_H -I/opt/hypertable/current/include \
       -I/opt/hypertable/current/include/thrift \
		-I/opt/hypertable/current/include/ThriftBroker/gen-cpp'

_LINKFLAGS = '-g -v -rdynamic -L/opt/hypertable/current/lib -lHyperThrift \
        -lHyperCommon -lHypertable -lthrift -levent -llog4cpp -lHyperSpace \
		-lboost_system-mt -lcurl -lpthread -lbson -lpcrecpp \
		-ljson_linux-gcc-4.2.1_libmt'

_CXX = ' clang++'# -Wc++11-extensions'

env = Environment(CCFLAGS='-g')
Program('suggest_test', 
['test.cpp',
'SuggestCore.cpp',
#'../htdba/htCollScanner.cpp',
#'../htdba/htCollWriter.cpp',
#'../htdba/htQuerier.cpp',
#'../htdba/htCustomScanner.cpp',
#'../htdba/htKeyScanner.cpp',
#'../htdba/tests/htDbaTests.cpp',
#'../htdba/htConnPool.cpp',
#'../tetramorph/threadpool/locks.cpp',
#'../tetramorph/threadpool/threadpool.cpp',
#'../tetramorph/threadpool/tasklauncher.cpp',
], LIBPATH='.', CCFLAGS=_CCFLAGS, LINKFLAGS=_LINKFLAGS, CXX = _CXX)
