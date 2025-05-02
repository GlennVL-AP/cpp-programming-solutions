find_package(Catch2 CONFIG REQUIRED)
include(Catch)

cpprog_add_test(
    TARGET test_cpprog
    CXX_SOURCES
    "cpprog.test.cpp"
)

cpprog_add_test(
    TARGET test_labo4_datetime
    CXX_SOURCES
    "labo4_datetime.test.cpp"
    DEPENDENCIES
    datetime
)

cpprog_add_test(
    TARGET test_labo7
    CXX_SOURCES
    "labo7_containsnumber.test.cpp"
    "labo7_fibonacci.test.cpp"
    DEPENDENCIES
    labo_7_ex_1_lib
    labo_7_ex_2_lib
)

cpprog_add_test(
    TARGET test_labo8
    CXX_SOURCES
    "labo8_datetime.test.cpp"
    DEPENDENCIES
    labo_8_datetime
)

cpprog_add_test(
    TARGET test_labo9
    CXX_SOURCES
    "labo9_vector.test.cpp"
    "labo9_matrix.test.cpp"
    "labo9_animals.test.cpp"
    "labo9_circularbuffer.test.cpp"
    DEPENDENCIES
    labo_9_lib
)

cpprog_add_test(
    TARGET test_labo10
    CXX_SOURCES
    "labo10_dynarray.test.cpp"
    DEPENDENCIES
    labo_10_lib
)
