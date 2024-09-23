#include <array>
#include <gtest/gtest.h>

#include <ioc/ioc.hpp>

#include <string>
#include <string_view>
#include <future>

using namespace std::string_view_literals;

struct Custom {
    Custom(int _num, const std::string_view _str) : num{_num}, str{_str} {}

    Custom() = default;

    [[nodiscard]]
    bool operator==(const Custom &) const = default;

    int num;
    std::string str;
};

class IocTest : public testing::Test {
public:
    void SetUp() override {
    }

    void TearDown() override {
        ioc::Ioc::clear();
    }
};

void CreateIoCDefault()
{
    ioc::Ioc ioc("default"sv); // default scope

    ioc.resolve<int, "int1", "Register">(5);
    ioc.resolve<std::string, "string1", "Register">("abc");

    ioc.resolve<int, "int2", "Register">(12);
    ioc.resolve<std::string, "string2", "Register">("def");

    ioc.resolve<Custom, "custom1", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("default"sv);
                                                    return new Custom(ioc.resolve<int, "int1", "Get">(),
                                                                    ioc.resolve<std::string, "string1", "Get">());
                                                });
    ioc.resolve<Custom, "custom2", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("default"sv);
                                                    return new Custom(ioc.resolve<int, "int2", "Get">(),
                                                                    ioc.resolve<std::string, "string2", "Get">());
                                                });
    ioc.resolve<Custom, "custom12", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("default"sv);
                                                    return new Custom(ioc.resolve<int, "int1", "Get">(),
                                                                    ioc.resolve<std::string, "string2", "Get">());
                                                });
    ioc.resolve<Custom, "custom21", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("default"sv);
                                                    return new Custom(ioc.resolve<int, "int2", "Get">(),
                                                                    ioc.resolve<std::string, "string1", "Get">());
                                                });
}

void CreateIoCOther()
{
    ioc::Ioc ioc("other"sv);

    ioc.resolve<int, "int1", "Register">(123);
    ioc.resolve<std::string, "string1", "Register">("abc_other");

    ioc.resolve<int, "int2", "Register">(321);
    ioc.resolve<std::string, "string2", "Register">("def_other");

    ioc.resolve<Custom, "custom1", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("other"sv);
                                                    return new Custom(ioc.resolve<int, "int1", "Get">(),
                                                                    ioc.resolve<std::string, "string1", "Get">());
                                                });
    ioc.resolve<Custom, "custom2", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("other"sv);
                                                    return new Custom(ioc.resolve<int, "int2", "Get">(),
                                                                    ioc.resolve<std::string, "string2", "Get">());
                                                });
    ioc.resolve<Custom, "custom12", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("other"sv);
                                                    return new Custom(ioc.resolve<int, "int1", "Get">(),
                                                                    ioc.resolve<std::string, "string2", "Get">());
                                                });
    ioc.resolve<Custom, "custom21", "Register">([]() -> Custom * {
                                                    ioc::Ioc ioc("other"sv);
                                                    return new Custom(ioc.resolve<int, "int2", "Get">(),
                                                                    ioc.resolve<std::string, "string1", "Get">());
                                                });
}


TEST_F(IocTest, Create) 
{
    CreateIoCDefault();

    ioc::Ioc iocDefault("default"sv);

    auto custom1 = iocDefault.resolve<Custom, "custom1", "Get">();
    auto custom2 = iocDefault.resolve<Custom, "custom2", "Get">();
    auto custom12 = iocDefault.resolve<Custom, "custom12", "Get">();
    auto custom21 = iocDefault.resolve<Custom, "custom21", "Get">();

    Custom expectedCustom1{5, "abc"sv};
    Custom expectedCustom2{12, "def"sv};
    Custom expectedCustom12{5,"def"sv};
    Custom expectedCustom21{12,"abc"sv};

    EXPECT_EQ(custom1, expectedCustom1);
    EXPECT_EQ(custom2, expectedCustom2);
    EXPECT_EQ(custom12, expectedCustom12);
    EXPECT_EQ(custom21, expectedCustom21);

    CreateIoCOther();

    ioc::Ioc iocOther("other"sv);

    auto customOther1 = iocOther.resolve<Custom, "custom1", "Get">();
    auto customOther2 = iocOther.resolve<Custom, "custom2", "Get">();
    auto customOther12 = iocOther.resolve<Custom, "custom12", "Get">();
    auto customOther21 = iocOther.resolve<Custom, "custom21", "Get">();

    Custom expectedCustomOther1{123, "abc_other"sv};
    Custom expectedCustomOther2{321, "def_other"sv};
    Custom expectedCustomOther12{123,"def_other"sv};
    Custom expectedCustomOther21{321,"abc_other"sv};

    EXPECT_EQ(customOther1, expectedCustomOther1);
    EXPECT_EQ(customOther2, expectedCustomOther2);
    EXPECT_EQ(customOther12, expectedCustomOther12);
    EXPECT_EQ(customOther21, expectedCustomOther21);
}


TEST_F(IocTest, MultiThread) 
{
    auto getExpected = [](std::string_view _scope) {
        std::array<Custom, 4> result;

        if(_scope == "default") {
            Custom expectedCustom1{5, "abc"sv};
            Custom expectedCustom2{12, "def"sv};
            Custom expectedCustom12{5,"def"sv};
            Custom expectedCustom21{12,"abc"sv};

            result = std::array{expectedCustom1, expectedCustom2, expectedCustom12, expectedCustom21};
        }
        if(_scope == "other") {
            Custom expectedCustom1{123, "abc_other"sv};
            Custom expectedCustom2{321, "def_other"sv};
            Custom expectedCustom12{123,"def_other"sv};
            Custom expectedCustom21{321,"abc_other"sv};

            result = std::array{expectedCustom1, expectedCustom2, expectedCustom12, expectedCustom21};
        }
        return result;
    };

    auto runner = [&](ioc::Ioc ioc){
        auto custom1 = ioc.resolve<Custom, "custom1", "Get">();
        auto custom2 = ioc.resolve<Custom, "custom2", "Get">();
        auto custom12 = ioc.resolve<Custom, "custom12", "Get">();
        auto custom21 = ioc.resolve<Custom, "custom21", "Get">();

        auto check = getExpected(ioc.name());

        EXPECT_EQ(custom1, check[0]);
        EXPECT_EQ(custom2, check[1]);
        EXPECT_EQ(custom12, check[2]);
        EXPECT_EQ(custom21, check[3]);
    };

    CreateIoCDefault();
    CreateIoCOther();

    ioc::Ioc ioc("default");
    ioc::Ioc iocOther("other");
    auto runner1 = std::bind(runner, ioc);
    auto runner2 = std::bind(runner, iocOther);

    auto result1 = std::async(std::launch::async, runner1);
    auto result2 = std::async(std::launch::async, runner2);
}