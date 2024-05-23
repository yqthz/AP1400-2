#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#define DEFCLASS(NAME, PRICE_UNIT) \
class NAME : public Ingredient { \
public: \
    NAME(size_t units) : Ingredient{PRICE_UNIT, units} { \
        this->name = #NAME; \
    } \
    virtual std::string get_name() override {\
        return this->name;   \
    }  \
};

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);


#endif  // SUB_INGREDIENTS_H