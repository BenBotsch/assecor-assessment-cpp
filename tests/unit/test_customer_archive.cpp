#include <gtest/gtest.h>
#include <optional>
#include <vector>
#include "customer/customer_archive.hpp"
#include "customer/storage.hpp"

namespace 
{
    class FakeStore : public customer::ICustomerStore 
    {
    public:
        bool add_return_value{true};
        std::optional<customer::Customer> get_return_value{};
        std::vector<customer::Customer> get_all_return_value{};

        int add_calls{0};
        int get_calls{0};
        int get_all_calls{0};
        customer::Customer last_added{};
        bool add(const customer::Customer& c) override 
        {
            ++add_calls;
            last_added = c;
            return add_return_value;
        }
        std::optional<customer::Customer> getById(int /*id*/) const override 
        {
            ++const_cast<FakeStore*>(this)->get_calls;
            return get_return_value;
        }
        std::vector<customer::Customer> getAll() const override 
        {
            ++const_cast<FakeStore*>(this)->get_all_calls;
            return get_all_return_value;
        }
    };
    customer::Customer makeValidCustomer(int id) 
    {
        customer::Customer c;
        c.id = id;
        c.first_name = "Hans";
        c.last_name = "M\xC3\xBCller";
        c.zip_code = "677742";
        c.city = "Lauterecken";
        c.favorite_color = customer::Color::Blue;
        return c;
    }
}

TEST(CustomerArchive, AddCustomerRejectsIncompleteCustomer) 
{
    auto store = std::make_shared<FakeStore>();
    customer::CustomerArchive archive(store);
    customer::Customer c = makeValidCustomer(1);
    c.city.clear();
    EXPECT_FALSE(archive.addCustomer(c));
    EXPECT_EQ(store->add_calls, 0);
}

TEST(CustomerArchive, AddCustomerRejectsTooLongFields) 
{
    auto store = std::make_shared<FakeStore>();
    customer::CustomerArchive archive(store);
    customer::Customer c = makeValidCustomer(1);
    c.first_name = std::string(customer::kFirstNameMax + 1, 'a');
    EXPECT_FALSE(archive.addCustomer(c));
    EXPECT_EQ(store->add_calls, 0);
}

TEST(CustomerArchive, AddCustomerDelegatesToStore) 
{
    auto store = std::make_shared<FakeStore>();
    customer::CustomerArchive archive(store);
    customer::Customer c = makeValidCustomer(42);
    EXPECT_TRUE(archive.addCustomer(c));
    EXPECT_EQ(store->add_calls, 1);
    EXPECT_EQ(store->last_added.id, 42);
    EXPECT_EQ(store->last_added.first_name, "Hans");
}

TEST(CustomerArchive, GetByIdDelegatesToStore) 
{
    auto store = std::make_shared<FakeStore>();
    store->get_return_value = makeValidCustomer(7);
    customer::CustomerArchive archive(store);
    const auto res = archive.getById(7);
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res->id, 7);
    EXPECT_EQ(store->get_calls, 1);
}

TEST(CustomerArchive, GetAllDelegatesToStore) 
{
    auto store = std::make_shared<FakeStore>();
    store->get_all_return_value = { makeValidCustomer(1), makeValidCustomer(2)};
    customer::CustomerArchive archive(store);
    const auto all = archive.getAll();
    EXPECT_EQ(all.size(), 2U);
    EXPECT_EQ(store->get_all_calls, 1);
}
