import java.util.*;

class Employee{
    String name;
    int id;
    String address;
    int salary;
    Employee(String name, int id, String address, int salary){
        this.name = name;
        this.id = id;
        this.address = address;
        this.salary = salary;
    }

    int getSal(){
        return salary;
    }
    String res(){
        return "Employee Name: "+name+"\nEmployee ID: "+id+"\nEmployee Address: "+address+"\nEmployee Salary: "+salary;
    }
}

class Dept{
    String name;
    String location;
    ArrayList<Employee> employees;
    Dept(String name,String location){
        this.name = name;
        this.location = location;
        this.employees = new ArrayList<>();
    }
    void add(Employee emp){
        employees.add(emp);
    }
    void remove(Employee emp){
        employees.remove(emp);
    }
    int yearExp(){
        int total = 0;
        for(Employee emp: employees){
            total += emp.getSal();
        }
        return total;
    }
    void display(){
        System.out.println("Department Name: "+name+"\nDepartment Location: "+location+"\nDepartment Employees:");
        for(Employee emp: employees){
            System.out.println(emp.res());
        }
    }

    public static void main(String[] args) {
        Dept itDept = new Dept("Information Technology", "SaltLake Campus");

        itDept.add(new Employee("Alice", 101, "123 Street A", 50000));
        itDept.add(new Employee("Bob", 102, "456 Street B", 60000));
        itDept.add(new Employee("Charlie", 103, "789 Street C", 55000));
        itDept.add(new Employee("Diana", 104, "321 Street D", 70000));
        itDept.add(new Employee("Eve", 105, "654 Street E", 52000));

        itDept.display();

        double expenditure = itDept.yearExp();
        System.out.println("\nYearly Expenditure for the Department: " + expenditure);
    }
}
