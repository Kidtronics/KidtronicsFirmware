//
//  var.h
//  DynamicTypedVariable
//
//  Created by Baixiao Huang on 7/29/18.
//  Copyright © 2018 Baixiao Huang. All rights reserved.
//

#ifndef var_h
#define var_h

class var {
public:
    enum VarType {
        INTEGER,
        STRING,
        BOOLEAN,
        DOUBLE
    };
private:
    // When var takes integer value, it is stored here.
    int m_integerValue;
    
    // When var takes string value, it is stored here.
    char* m_stringValue = nullptr;

    // When var takes boolean value, it is stored here.
    bool m_booleanValue;

    // When var takes double value, it is stored here.
    double m_doubleValue;
    
    // Variable type currently this var is using.
    enum VarType m_currentType;
    
    // Copy the other variable into itself.
    void copy(const var& other);

    // Get value in double
    double getValueAsDouble() const;
    
public:
    // Construct integer var.
    var(int integer);
    // Construct string var.
    var(const char* string);
    // Copy construct bool var.
    var(bool boolean);
    // Copy construction double var.
    var(double doubleVar);
    // Copy construct var.
    var(const var& otherVar);
    
    // Destructor
    ~var();
    
    // Assignment operator.
    var& operator=(const var& other);

    VarType getType(){return m_currentType;}
    
    // Comparison operators.
    friend bool operator==(const var& lhs, const var& rhs);
    friend bool operator!=(const var& lhs, const var& rhs);
    friend bool operator>(const var& lhs, const var& rhs);
    friend bool operator>=(const var& lhs, const var& rhs);
    friend bool operator<(const var& lhs, const var& rhs);
    friend bool operator<=(const var& lhs, const var& rhs);
    
    // Arithmatic operators.
    friend var operator+(var lhs, const var& rhs);
    friend var operator-(var lhs, const var& rhs);
    
    // Unary operators.
    // Prefix increment operator.
    var& operator++();
    
    // Posfix increment operator.
    var operator++(int);
    
    // Prefix decrement operator.
    var& operator--();
    
    // Posfix decrement operator.
    var operator--(int);
    
    // Conversion to bool.
    explicit operator bool() const;
};

#endif /* var_h */
