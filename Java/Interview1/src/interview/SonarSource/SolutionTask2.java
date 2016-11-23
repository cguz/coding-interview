package interview.SonarSource;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class SolutionTask2 {

	   
	static SolutionTask2 sol = new SolutionTask2();
    
    public static void main(String[] args) throws FileNotFoundException {
    	
    	File file = new File("./TEST/interview/SonarSource/input-test3.txt");
    	Scanner in = new Scanner(file);
    	// Scanner in = new Scanner(System.in);

 		// creating the set of nodes of the undirected graph
 		int N = in.nextInt();
 		
    	int[] board = new int[N];
    	for(int i=0; i < N;++i){
    		board[i] = in.nextInt();
    	}
    	
    	System.out.println(solution(board));
 		
    }
    
    private static int solution(int[] A) {
    	
    	int min=1000000000, max=-1000000000;
    	
    	for(int i=0; i < A.length; i++){
    		if(A[i]< min)
    			min = A[i];
    		if(A[i] > max)
    			max = A[i];
    	}
    	
    	return abs(max-min);
	}
    
    private static int abs(int i) {
		return (i<0)?i*-1:i;
	}

	
}
