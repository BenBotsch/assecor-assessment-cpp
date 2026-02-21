#pragma once
#include <memory>
#include <optional>
#include <vector>
#include "customer.h"
#include "customer/storage.hpp"

namespace customer 
{
    class ICustomerArchiveReader 
    {
    public:
        virtual ~ICustomerArchiveReader() = default;
        virtual std::optional<Customer> getById(int id) const = 0;
        virtual std::vector<Customer> getAll() const = 0;
    };
    class CustomerArchive : public ICustomerArchiveReader 
    {
    public:
        CustomerArchive();
        explicit CustomerArchive(std::shared_ptr<ICustomerStore> store);
        bool addCustomer(const Customer& customer);
        std::optional<Customer> getById(int id) const override;
        std::vector<Customer> getAll() const override;

    private:
        std::shared_ptr<ICustomerStore> store_;
    };
}
