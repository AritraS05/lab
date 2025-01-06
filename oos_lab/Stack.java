class Stack{
    int[] arr;
    int top;
    int capacity;

    Stack(int size){
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }
    void push(int val){
        if(top == capacity - 1){
            System.out.println("stack full");
            return;
        }
        arr[++top] = val;
    }

    void pop(){
        if(top == -1){
            System.out.println("stack empty");
            return;
        }
        top--;
    }
    void print(){
        if(top == -1){
            System.out.println("Stack is empty:");
            return;
        }
        System.out.println("Stack elements are:");
        for(int i = 0; i<=top; i++){
            System.out.println(arr[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Stack st = new Stack(30);
        st.push(30);
        st.push(30);
        st.push(30);
        st.push(30);
        st.push(30);
        st.push(30);

        System.out.println("Printing the stack: ");
        st.print();

        st.pop();
        st.pop();
        st.pop();
        st.pop();
        
        System.out.println("Stack after popping: ");
        st.print();
    }
}
