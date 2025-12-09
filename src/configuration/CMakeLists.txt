add_subdirectory(tests)

list(APPEND SOURCES
    src/configuration/cliargumentparser.cpp
)

set(SOURCES "${SOURCES}" PARENT_SCOPE)
set(TESTSOURCES "${TESTSOURCES}" PARENT_SCOPE)