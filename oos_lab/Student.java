class Student{
    String name;
    int s1,s2,s3;
    public Student(String name, int m1, int m2, int m3) {
        this.name = name;
        this.s1 = m1;
        this.s2 = m2;
        this.s3 = m3;
    }
    double average() {
        return (s1 + s2 + s3) / 3.0; 
    }
    void display() {
        System.out.println("Name: " + name);
        System.out.println("Total: " + (s1 + s2 + s3));
        System.out.println("Average: " + average());
    }

    public static void main(String args[]) {
        Student s1 = new Student("Aritra", 100, 99, 90); 
        s1.display();
    }
}
