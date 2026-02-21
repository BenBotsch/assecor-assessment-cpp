#include <gtest/gtest.h>
#include <memory>
#include "customer/customer_archive.hpp"
#include "customer/customer_formatter.hpp"

namespace 
{
    customer::Customer makeCustomer(int id, std::string first, std::string last) 
    {
        customer::Customer c;
        c.id = id;
        c.first_name = std::move(first);
        c.last_name = std::move(last);
        c.zip_code = "10115";
        c.city = "Berlin";
        c.favorite_color = customer::Color::Green;
        return c;
    }
}

TEST(Integration, ArchiveAndFormatterWorkTogether) 
{
    auto archive = std::make_shared<customer::CustomerArchive>();
    customer::CustomerFormatter formatter(archive);
    ASSERT_TRUE(archive->addCustomer(makeCustomer(1, "Alice", "Example")));
    ASSERT_TRUE(archive->addCustomer(makeCustomer(2, "Bob", "Sample")));
    EXPECT_EQ(formatter.formatById(1), "Example, Alice, 10115 Berlin, Gr\xC3\xBCn");
    EXPECT_EQ(formatter.formatById(999), "(kein Kunde)");
    const auto all = archive->getAll();
    ASSERT_EQ(all.size(), 2U);
    EXPECT_FALSE(archive->addCustomer(makeCustomer(2, "Other", "Person")));
    EXPECT_EQ(archive->getAll().size(), 2U);
}
