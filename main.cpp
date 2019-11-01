//Ильминский Никита М80-207Б-18
/*Создать класс Money для работы с денежными суммами. Сумма денег должна быть представлено двумя
полями: типа unsigned long long для рублей и типа unsigned char – для копеек. Дробная часть (копейки) при
выводе на экран должна быть отделена от целой части запятой. Реализовать сложение сумм, вычитание,
деление сумм, деление суммы на дробное число, умножение на дробное число и операции сравнения.*/

/*Операции сложения, вычитания, умножения, деления, сравнения (на равенство, больше и меньше)
должны быть выполнены в виде перегрузки операторов.
Необходимо реализовать пользовательский литерал для работы с константами типа Money.*/


#include <iostream>
#include <cmath>

using namespace std;

class Money {
    unsigned long long rub;
    unsigned char kop;
public:
    Money(int r, int p) {
        setRub(r);
        setKop(p);
    }
    void setRub(int r) {
        rub = r;
    }
    void setKop(int p) {
        kop = p;
    }
    int getRub() {
        return rub;
    }
    int getKop() {
        return kop;
    }
    int conv() {
        return rub * 100 + kop;
    }

    friend Money operator+ (Money m1, Money m2);
    friend Money operator- (Money m1, Money m2);
    friend Money operator* (Money m1, double mult);
    friend double operator/ (Money m1, Money m2);
    friend bool operator< (Money m1, Money m2);
    friend bool operator== (Money m1, Money m2);
    friend bool operator!= (Money m1, Money m2);
    friend bool operator> (Money m1, Money m2);

    double fraction_div(double div) {
        return conv() / div / 100;
    }
};

//OPERATOR OVERLOAD
Money operator+ (Money m1, Money m2) {
    Money result(0, 0);
    int p = m1.getKop() + m2.getKop();
    int r = m1.getRub() + m2.getRub();
    result.setRub(r + p / 100);
    result.setKop(p % 100);
    return result;
}

Money operator- (Money m1, Money m2) {
    Money result(0, 0);
    int p, r;
    if (m1 < m2) {
        p = m2.getKop() - m1.getKop();
        r = m2.getRub() - m1.getRub();
    } else {
        p = m1.getKop() - m2.getKop();
        r = m1.getRub() - m2.getRub();
    }
    if (p < 0) {
        p = 100 + p;
        r--;
    }
    result.setRub(r);
    result.setKop(p);
    return result;
}

Money operator* (Money m, double mult) {
    Money result(0, 0);
    result.setKop(fmod(abs(m.conv() * mult), 100));
    result.setRub(abs(m.conv() * mult) / 100);
    return result;
}

double operator/ (Money m1, Money m2) {
    return (double)m1.conv() / (double)m2.conv();
}

bool operator< (Money m1, Money m2) {
    return m1.conv() < m2.conv();
}

bool operator> (Money m1, Money m2) {
    return m1.conv() > m2.conv();
}

bool operator== (Money m1, Money m2) {
    return m1.conv() == m2.conv();
}

bool operator!= (Money m1, Money m2) {
    return !(m1 == m2);
}

//UDL
Money operator"" _r(unsigned long long rub) {
    return Money(rub, 0);
}

Money operator"" _k(unsigned long long kop) {
    return Money(kop / 100, kop % 100);
}

Money operator"" _rk(long double rub_kop) {
    int sum = rub_kop * 100;
    return Money(sum / 100, sum % 100);
}

int main()
{
    Money cash1 = 2988770_r;
    Money cash2 = 23.45_rk;

    Money cash3 = 99_k;
    Money cash4 = 687_k;

    Money cash5 = 2_r + 93_k;
    Money cash6 = 0_r + 10_k;

    Money cash7 = 0_r + 45879_k;
    Money cash8 = 0_k;

    cout << "cash1 is " << cash1.getRub() << " rub, " << cash1.getKop() << " kop\n";
    cout << "cash2 is " << cash2.getRub() << " rub, " << cash2.getKop() << " kop\n";
    cout << "cash3 is " << cash3.getRub() << " rub, " << cash3.getKop() << " kop\n";
    cout << "cash4 is " << cash4.getRub() << " rub, " << cash4.getKop() << " kop\n";
    cout << "cash5 is " << cash5.getRub() << " rub, " << cash5.getKop() << " kop\n";
    cout << "cash6 is " << cash6.getRub() << " rub, " << cash6.getKop() << " kop\n";
    cout << "cash7 is " << cash7.getRub() << " rub, " << cash7.getKop() << " kop\n";
    cout << "cash8 is " << cash8.getRub() << " rub, " << cash8.getKop() << " kop\n\n";

    cout << "The results of operations:\n";

    cout << "Addition:\n";
    Money res = cash1 + cash2;
    cout << "cash1 + cash2 is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    res = cash3 + cash4;
    cout << "cash3 + cash4 is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    res = cash5 + cash6;
    cout << "cash5 + cash6 is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    res = cash7 + cash8;
    cout << "cash7 + cash8 is " << res.getRub() << " rub, " << res.getKop() << " kop\n\n";

    cout << "Substraction:\n";
    res = cash1 - cash2;
    if (cash1 < cash2) {
        cout << "cash1 - cash2 is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash1 - cash2 is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash3 - cash4;
    if (cash3 < cash4) {
        cout << "cash3 - cash4 is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash3 - cash4 is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash5 - cash6;
    if (cash5 < cash6) {
        cout << "cash5 - cash6 is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash5 - cash6 is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash7 - cash8;
    if (cash7 < cash8) {
        cout << "cash7 - cash8 is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash7 - cash8 is " << res.getRub() << " rub, " << res.getKop() << " kop\n\n";
    }

    cout << "Division:\n";
    if (cash2.conv() == 0) {
        cout << "Can't divide: cash2 is 0! Aborting...\n\n";
    } else {
        cout << "cash1 div cash2 is " << cash1 / cash2 << endl << endl;
    }
    if (cash4.conv() == 0) {
        cout << "Can't divide: cash2 is 0! Aborting...\n\n";
    } else {
        cout << "cash3 div cash4 is " << cash3 / cash4 << endl << endl;
    }
    if (cash6.conv() == 0) {
        cout << "Can't divide: cash2 is 0! Aborting...\n\n";
    } else {
        cout << "cash5 div cash6 is " << cash5 / cash6 << endl << endl;
    }
    if (cash8.conv() == 0) {
        cout << "Can't divide: cash2 is 0! Aborting...\n\n";
    } else {
        cout << "cash7 div cash8 is " << cash7 / cash8 << endl << endl;
    }

    cout << "Multiplication:\n";
    double mult;
    cout << "Enter the desired multiplicator value:\n";
    cin >> mult;

    res = cash1 * mult;
    if (mult < 0) {
        cout << "cash1 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash1 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash2 * mult;
    if (mult < 0) {
        cout << "cash2 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash2 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash3 * mult;
    if (mult < 0) {
        cout << "cash3 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash3 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash4 * mult;
    if (mult < 0) {
        cout << "cash4 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash4 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash5 * mult;
    if (mult < 0) {
        cout << "cash5 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash5 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash6 * mult;
    if (mult < 0) {
        cout << "cash6 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash6 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash7 * mult;
    if (mult < 0) {
        cout << "cash7 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n";
    } else {
        cout << "cash7 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n";
    }
    res = cash8 * mult;
    if (mult < 0) {
        cout << "cash8 mult " << mult << " is -" << res.getRub() << " rub, " << res.getKop() << " kop\n\n";
    } else {
        cout << "cash8 mult " << mult << " is " << res.getRub() << " rub, " << res.getKop() << " kop\n\n";
    }

    cout << "Comparision:\n";
    cout << "cash1 < cash2?: " << (cash1 < cash2 ? "yes" : "no") << endl;
    cout << "cash3 = cash4?: " << (cash1 == cash2 ? "yes" : "no") << endl;
    cout << "cash5 != cash6?: " << (cash1 != cash2 ? "yes" : "no") << endl;
    cout << "cash7 > cash8?: " << (cash1 > cash2 ? "yes" : "no") << endl << endl;

    return 0;
}
