//try this later -->maybe use of abstract class is there 
import java.util.ArrayList;


class Publication{
    int noOfPages,price;
    String publisherName;
    Publication(int noOfPages,int price,String publisher){
        this.noOfPages = noOfPages;
        this.price = price;
        this.publisherName = publisher;
    }
    class Book{
        String name;
        Book(String name){
            this.name = name;
        }
    }
    class Journal{
        String name;
        Journal(String name){
            this.name = name;
        }
    }
}

class Library{
    ArrayList<Publication> publications;
    public static void main(String[] args) {
        Library lib = new Library();
    }
} 
