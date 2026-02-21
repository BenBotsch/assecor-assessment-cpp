#ifndef __DEFINED_CUSTOMER_H
#define __DEFINED_CUSTOMER_H

#define	COLOR_BLUE      1
#define COLOR_GREEN     2
#define COLOR_VIOLET    3
#define COLOR_RED       4
#define COLOR_YELLOW    5
#define COLOR_TURQUOISE 6
#define COLOR_WHITE     7

struct _CUSTOMER 
{
    int id;
    char first_name[24];
    char last_name[32];
    char zip_code[8];
    char city[32];
    int favorite_color;
};

typedef struct _CUSTOMER CUSTOMER;

#ifdef __cplusplus

#include <cstddef>
#include <cstring>
#include <optional>
#include <string>
#include <string_view>

namespace customer 
{
    enum class Color : int 
    {
        Blue = COLOR_BLUE,
        Green = COLOR_GREEN,
        Violet = COLOR_VIOLET,
        Red = COLOR_RED,
        Yellow = COLOR_YELLOW,
        Turquoise = COLOR_TURQUOISE,
        White = COLOR_WHITE
    };
    inline std::string_view toGermanString(Color color) noexcept 
    {
        switch (color) 
        {
            case Color::Blue: return "Blau";
            case Color::Green: return "Gr\xC3\xBCn";
            case Color::Violet: return "Violett";
            case Color::Red: return "Rot";
            case Color::Yellow: return "Gelb";
            case Color::Turquoise: return "T\xC3\xBCrkis";
            case Color::White: return "Wei\xC3\x9F";
            default: return "(unbekannt)";
        }
    }
    inline constexpr std::size_t kFirstNameMax = sizeof(((CUSTOMER*)nullptr)->first_name) - 1;
    inline constexpr std::size_t kLastNameMax  = sizeof(((CUSTOMER*)nullptr)->last_name) - 1;
    inline constexpr std::size_t kZipCodeMax   = sizeof(((CUSTOMER*)nullptr)->zip_code) - 1;
    inline constexpr std::size_t kCityMax      = sizeof(((CUSTOMER*)nullptr)->city) - 1;

    struct Customer 
    {
        int id{};
        std::string first_name;
        std::string last_name;
        std::string zip_code;
        std::string city;
        Color favorite_color{Color::Blue};

        bool isComplete() const 
        {
            return id > 0 &&
                   !first_name.empty() && !last_name.empty() &&
                   !zip_code.empty() && !city.empty();
        }
    };
    inline bool fitsLegacy(const Customer& c) 
    {
        return c.first_name.size() <= kFirstNameMax &&
               c.last_name.size()  <= kLastNameMax &&
               c.zip_code.size()   <= kZipCodeMax &&
               c.city.size()       <= kCityMax;
    }
    inline Customer fromLegacy(const CUSTOMER& legacy) 
    {
        Customer c;
        c.id = legacy.id;
        c.first_name = legacy.first_name;
        c.last_name = legacy.last_name;
        c.zip_code = legacy.zip_code;
        c.city = legacy.city;
        c.favorite_color = static_cast<Color>(legacy.favorite_color);
        return c;
    }
    inline void copyChecked(char* dest, std::size_t dest_size, std::string_view src) 
    {
        std::memset(dest, 0, dest_size);
        const std::size_t n = (src.size() < dest_size) ? src.size() : (dest_size - 1);
        if (n > 0) 
        {
            std::memcpy(dest, src.data(), n);
        }
        dest[n] = '\0';
    }
    inline std::optional<CUSTOMER> toLegacy(const Customer& c) 
    {
        if (!c.isComplete() || !fitsLegacy(c)) 
        {
            return std::nullopt;
        }
        CUSTOMER legacy{};
        legacy.id = c.id;
        copyChecked(legacy.first_name, sizeof(legacy.first_name), c.first_name);
        copyChecked(legacy.last_name, sizeof(legacy.last_name), c.last_name);
        copyChecked(legacy.zip_code, sizeof(legacy.zip_code), c.zip_code);
        copyChecked(legacy.city, sizeof(legacy.city), c.city);
        legacy.favorite_color = static_cast<int>(c.favorite_color);
        return legacy;
    }
}
#endif
#endif
