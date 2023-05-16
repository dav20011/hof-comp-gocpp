struct Closure {
    int a;

    int operator()(int b) {
        return a + b;
    }
};

Closure createAdd(int a) {
    return {a};
}

int add(int a, int b) {
    return createAdd(a)(b);
}
