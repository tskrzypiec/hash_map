//#include <gtest/gtest.h>
#include <functional>
#include <map>

#include <string>

struct Hash {
    using Int = std::int64_t;
    Hash(const std::string& v) {
        auto h = std::hash<std::string>{};
        value = h(v);
    }
    Int value;
};

struct HashCompare {
    bool operator()( const Hash& lhs, const Hash& rhs) const {
        return true;
    }
};


using MyMap = std::map<Hash, std::string, HashCompare>;

struct HashMap {

    HashMap() : _map ( HashCompare{} ) {}
    void put(const std::string& key, const std::string& data) {
        _map[Hash { key } ] = data;
    }

    bool check(const std::string& key) const noexcept {
        return _map.find(Hash { key } ) != _map.end();
    }

    std::string at(const std::string& key) {
        return _map.at(Hash { key } );
    }

    bool empty() const noexcept { return _map.empty(); }

    MyMap _map;
};

TEST(MyMap, simple) {
    HashMap asd;

    EXPECT_ANY_THROW(asd.at(""));
    EXPECT_FALSE(asd.check("bird"));

    asd.put("bird", "a bird is ... ");
    asd.put("bird", "");
    EXPECT_TRUE(asd.check("bird"));
    EXPECT_EQ(asd.at("bird"), std::string{""});
}

int main(int argc, char** argv) {
   // ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

