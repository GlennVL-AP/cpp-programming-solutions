cpprog_add_library(
    TARGET labo_8_datetime
    CXX_MODULES
    "yearmonthday.cpp"
    "leapyear.cpp"
    "dateverification.cpp"
    "date.cpp"
    "datetime.cpp"
)

cpprog_add_executable(
    TARGET labo_8_ex_1
    CXX_SOURCES
    "main.cpp"
    DEPENDENCIES
    labo_8_datetime
)
