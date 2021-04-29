// ---------------------------------------------------------------------------------------------------------
/* 
    ----A----
    |       |
    F       B
    |___G___|
    |       |
    E       C
    |       |
    ----D----   DP (dot)
*/
// ---------------------------------------------------------------------------------------------------------
// PinMode

// 7seg
const int digit_1 = 13;
const int digit_2 = 9;
const int digit_3 = 10;
const int digit_4 = 7;
const int A = 12;
const int B = 11;
const int C = 5;
const int D = 3;
const int E = 2;
const int F = 8;
const int G = 6;
// const int DP = 4;

// button
int set_btn_1 = A0;
int set_btn_2 = A1;
int set_btn_3 = A2;

// buzzer
int buzzer = 4;

// ---------------------------------------------------------------------------------------------------------
// Variable

// display
int num_7seg[4] = {0, 0, 0, 0};
// password
int num_password[4] = {1, 2, 3, 4};

int digit = 0;
int num_password_true = 0;
int btn_1 = 0, btn_2 = 0, btn_3 = 0;
boolean btn_bool_1 = false, btn_bool_2 = false, btn_bool_3 = false;
boolean btn_bool_1_do, btn_bool_2_do, btn_bool_3_do;
boolean check_enter = false;

// ---------------------------------------------------------------------------------------------------------
// Main

void setup()
{
    pinMode(digit_1, OUTPUT);
    pinMode(digit_2, OUTPUT);
    pinMode(digit_3, OUTPUT);
    pinMode(digit_4, OUTPUT);

    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    // pinMode(DP, OUTPUT);
    // digitalWrite(DP, LOW);

    pinMode(set_btn_1, INPUT_PULLUP);
    pinMode(set_btn_2, INPUT_PULLUP);
    pinMode(set_btn_3, INPUT_PULLUP);

    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    // btn_1
    if (analogRead(set_btn_1) < 980)
    {
        btn_bool_1 = true;
    }
    else
    {
        btn_bool_1 = false;
        btn_bool_1_do = false;
    }

    if (btn_bool_1 == true && btn_bool_1_do == false)
    {
        num_7seg[digit] = check_num_1();
        digit++;
        btn_bool_1_do = true;
    }

    // btn_2
    if (analogRead(set_btn_2) < 980)
    {
        btn_bool_2 = true;
    }
    else
    {
        btn_bool_2 = false;
        btn_bool_2_do = false;
    }

    if (btn_bool_2 == true && btn_bool_2_do == false)
    {
        num_7seg[digit] = check_num_2();
        digit++;
        btn_bool_2_do = true;
    }

    // btn_3
    if (analogRead(set_btn_3) < 980)
    {
        btn_bool_3 = true;
    }
    else
    {
        btn_bool_3 = false;
        btn_bool_3_do = false;
    }

    if (btn_bool_3 == true && btn_bool_3_do == false)
    {
        int temp = check_num_3();
        if (temp < 10)
        {
            num_7seg[digit] = temp;
            digit++;
        }
        else if (temp == 11)
        {
            for (int i = 0; i < 4; i++)
            {
                if (num_7seg[i] == num_password[i])
                    num_password_true++;
                else
                    num_password_true = 0;
            }
            check_enter = true;
        }
        else if (temp == 12)
        {
            num_7seg[0] = 0;
            num_7seg[1] = 0;
            num_7seg[2] = 0;
            num_7seg[3] = 0;
            digit = 0;
        }
        btn_bool_3_do = true;
    }

    // btn_enter
    if (check_enter == true)
    {
        if (num_password_true == 4)
        {
            beep(50);
            num_7seg[0] = 0;
            num_7seg[1] = 0;
            num_7seg[2] = 0;
            num_7seg[3] = 0;
            digit = 0;
            num_password_true = 0;
            delay(50);
            beep(50);
        }
        else
        {
            beep(1000);
            num_7seg[0] = 0;
            num_7seg[1] = 0;
            num_7seg[2] = 0;
            num_7seg[3] = 0;
            digit = 0;
            num_password_true = 0;
        }
        check_enter = false;
    }

    // display 7seg
    for (int i = 1; i <= 4; i++)
    {
        print_digit(i);
        print_number(num_7seg[i - 1]);
        delay(2);
    }

    // Serial.println((String) "Btn1: " + analogRead(A0) + "\tBtn2: " + analogRead(A1) + "\tBtn3: " + analogRead(A2) + "\tDigit: " + digit + "\t" + num_7seg[0] + num_7seg[1] + num_7seg[2] + num_7seg[3]);
}

// ---------------------------------------------------------------------------------------------------------
// Class

int check_num_1()
{
    int temp_num = 0;
    int btn = analogRead(set_btn_1);
    if (btn < 900 && btn > 700)
    {
        temp_num = 1;
    }
    else if (btn < 700 && btn > 600)
    {
        temp_num = 2;
    }
    else if (btn < 500 && btn > 400)
    {
        temp_num = 3;
    }
    else if (btn < 400 && btn > 200)
    {
        temp_num = 4;
    }

    return temp_num;
}

int check_num_2()
{
    int temp_num = 0;
    int btn = analogRead(set_btn_2);
    if (btn < 900 && btn > 700)
    {
        temp_num = 5;
    }
    else if (btn < 700 && btn > 600)
    {
        temp_num = 6;
    }
    else if (btn < 500 && btn > 400)
    {
        temp_num = 7;
    }
    else if (btn < 400 && btn > 200)
    {
        temp_num = 8;
    }

    return temp_num;
}

int check_num_3()
{
    int temp_num = 0;
    int btn = analogRead(set_btn_3);
    if (btn < 900 && btn > 700)
    {
        temp_num = 9;
    }
    else if (btn < 700 && btn > 600)
    {
        temp_num = 0;
    }
    else if (btn < 500 && btn > 400)
    { // enter
        temp_num = 11;
    }
    else if (btn < 400 && btn > 200)
    { // reset
        temp_num = 12;
    }

    return temp_num;
}

void beep(int delayms)
{
    digitalWrite(buzzer, HIGH);
    delay(delayms);
    digitalWrite(buzzer, LOW);
}

void print_digit(int digit)
{
    switch (digit)
    {
    case 1:
        digitalWrite(digit_1, LOW);
        digitalWrite(digit_2, HIGH);
        digitalWrite(digit_3, HIGH);
        digitalWrite(digit_4, HIGH);
        break;
    case 2:
        digitalWrite(digit_1, HIGH);
        digitalWrite(digit_2, LOW);
        digitalWrite(digit_3, HIGH);
        digitalWrite(digit_4, HIGH);
        break;
    case 3:
        digitalWrite(digit_1, HIGH);
        digitalWrite(digit_2, HIGH);
        digitalWrite(digit_3, LOW);
        digitalWrite(digit_4, HIGH);
        break;
    case 4:
        digitalWrite(digit_1, HIGH);
        digitalWrite(digit_2, HIGH);
        digitalWrite(digit_3, HIGH);
        digitalWrite(digit_4, LOW);
        break;
    default:
        break;
    }
}

void print_number(int number)
{
    switch (number)
    {
    case 0:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, LOW);
        break;
    case 1:
        digitalWrite(A, LOW);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
    case 2:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, LOW);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, LOW);
        digitalWrite(G, HIGH);
        break;
    case 3:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, HIGH);
        break;
    case 4:
        digitalWrite(A, LOW);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 5:
        digitalWrite(A, HIGH);
        digitalWrite(B, LOW);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 6:
        digitalWrite(A, HIGH);
        digitalWrite(B, LOW);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 7:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
    case 8:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    case 9:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, LOW);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;
    default:
        break;
    }
}