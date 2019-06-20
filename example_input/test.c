   int b = 5;
    int a = 1+ b*5;
//     int c = 252 / 2;
//     float d = a / b;
//     print(a);
// print(b);
// print(c);
// print(d);
// print("-----");
//     float e = 10.4 / 1.1;
//     int f = e;

//     a += 10;
//     b -= 1.3;
//     c *= 3.2;
//     d /= 2;

//     // float a;
//     // float b = 1.67;
//     // float c = 2;
//     // float d = 4.5 + b;
//     // float e = foo(b, b);
//     // float f = foo(b, b) - 2;
// print(a);
// print(b);
// print(c);
// print(d);
// print(e);
// print(f);
    // float x =  8+a*45 + (2.5*(8+7))/ 3 ;
    // print(x);
    // print("Srting");
    // print(k);
    // float p = foo(a, a);
    // print(p);



// error handler - not divid 0 & mod needs to be int
int a = 100;
    int b = 0;

    int c;
    int d;

    c = 100 / b;
    print(c);
    d = 100 /0;
    print(d);

    c = 20.3 % 2;
    c = 20 % 2.0;
    c = 20.3 % 2.4;
    d = 20 % 2;
    print(c);
    print(d);
 

 // error handler - wrong function input
 int a =10;
    int b = 12;
    float c = 12.4;
    float d = 17.1;

    int out;
    out = foo(a, b);
    out = foo(a, c);
    out = foo(c, a);
    out = foo(c, d);
    out = foo(a, a, a);