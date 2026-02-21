#include "customer/customer_formatter.hpp"
#include <sstream>
#include <stdexcept>

namespace customer 
{
    CustomerFormatter::CustomerFormatter(std::shared_ptr<const ICustomerArchiveReader> archive_reader)
        : archive_reader_(std::move(archive_reader)) 
    {
        if (!archive_reader_) 
        {
            throw std::invalid_argument("archive_reader must not be null");
        }
    }
    std::string CustomerFormatter::formatById(int id) const 
    {
        const auto customer = archive_reader_->getById(id);
        if (!customer.has_value()) 
        {
            return "(kein Kunde)";
        }
        std::ostringstream oss;
        oss << customer->last_name << ", "
            << customer->first_name << ", "
            << customer->zip_code << " " << customer->city << ", "
            << toGermanString(customer->favorite_color);
        return oss.str();
    }
}
