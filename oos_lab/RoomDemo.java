class Room{
    int height,width,breadth;
    Room(int h,int w,int b){
        height = h;
        width = w;
        breadth = b;
    }
    int volume(){
        return height*width*breadth;
    }
}

class RoomDemo{
    public static void main(String args[]){
        Room r1 = new Room(10,20,30);
        Room r2 = new Room(20,30,40);
        System.out.println("volume of room 1:" + r1.volume());
        System.out.println("volume of room 2:" + r2.volume());
    }
}