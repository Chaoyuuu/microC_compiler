int foo() {
   int d = 8;
    d += 10;
   
    print(d);
    return d;
}

void lol(int a) {
    print(a);
	return;
}

void main(){
   int a = 5;
   // a = foo(4);
   lol(a);
   return;
}

