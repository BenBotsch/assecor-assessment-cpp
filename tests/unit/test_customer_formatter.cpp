#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <vector>
#include "customer/customer_formatter.hpp"

namespace 
{
    class FakeArchiveReader : public customer::ICustomerArchiveReader 
    {
    public:
        std::optional<customer::Customer> get_return_value{};
        std::vector<customer::Customer> get_all_return_value{};
        int get_calls{0};
        std::optional<customer::Customer> getById(int /*id*/) const override 
        {
            ++const_cast<FakeArchiveReader*>(this)->get_calls;
            return get_return_value;
        }
        std::vector<customer::Customer> getAll() const override 
        {
            return get_all_return_value;
        }
    };
    customer::Customer sample_customer() 
    {
        customer::Customer c;
        c.id = 10;
        c.first_name = "Hans";
        c.last_name = "M\xC3\xBCller";
        c.zip_code = "677742";
        c.city = "Lauterecken";
        c.favorite_color = customer::Color::Blue;
        return c;
    }
} 

TEST(CustomerFormatter, FormatsNotFoundCustomer) 
{
    auto reader = std::make_shared<FakeArchiveReader>();
    customer::CustomerFormatter formatter(reader);
    EXPECT_EQ(formatter.formatById(123), "(kein Kunde)");
    EXPECT_EQ(reader->get_calls, 1);
}

TEST(CustomerFormatter, FormatsFoundCustomer) 
{
    auto reader = std::make_shared<FakeArchiveReader>();
    reader->get_return_value = sample_customer();
    customer::CustomerFormatter formatter(reader);
    EXPECT_EQ(
        formatter.formatById(10),
        std::string("M\xC3\xBCller, Hans, 677742 Lauterecken, Blau"));
    EXPECT_EQ(reader->get_calls, 1);
}
