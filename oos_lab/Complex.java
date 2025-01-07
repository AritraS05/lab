class Complex{
    int real,imaginary;
    Complex(){
        this.real = 0;
        this.imaginary = 0;
    }
    Complex(int real){
        this.real = real;
        this.imaginary = 0;
    }
    Complex(int real,int imaginary){
        this.real = real;
        this.imaginary = imaginary;
    }
    Complex sum(Complex c1,Complex c2){
        Complex c3 = new Complex();
        c3.real = c1.real + c2.real;
        c3.imaginary = c1.imaginary + c2.imaginary;
        return c3;
    }
    Complex product(Complex c1,Complex c2){
        Complex c3 = new Complex();
        c3.real = (c1.real*c2.real) - (c1.imaginary*c2.imaginary);
        c3.imaginary = (c1.real*c2.imaginary) + (c1.imaginary*c2.real);
        return c3;
    }
    void display(){
        System.out.println(real + " + " + imaginary + "i");
    }
    public static void main(String[] args) {
        Complex c1 = new Complex(3,2);
        Complex c2= new Complex(4,-2);
        Complex c3 = c1.sum(c2,c1);
        c3.display();
        Complex c4 = c1.product(c2,c1);
        c4.display();
    }
}