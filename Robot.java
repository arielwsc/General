package arielcarvalhoassignment6;
        
public class Robot extends Labyrinth{
    private int row;
    private int column;
    private boolean endLabyrinth = false;
    private static int[] backTrackingRow = new int[30];
    private static int[] backTrackingColumn = new int[30];
    private int k = 1;
    
    public Robot(int startingRowPoint, int startingColumnPoint){
        row = startingRowPoint;
        column = startingColumnPoint;
        backTrackingRow[0] = row;
        backTrackingColumn[0] = column;
    }
    
    public boolean findPath(){
        int stepsCounter =0;
        
        while(stepsCounter <= 30 && !endLabyrinth){
            switch(nextStep()){
                case 0:
                    row = backTrackingRow[k];
                    column = backTrackingColumn[k];
                    break;
                case 1:
                    moveForward();
                    stepsCounter++;
                    break;
                case 2:
                    moveRight();
                    stepsCounter++;
                    break;
                case 3:
                    moveLeft();
                    stepsCounter++;
                    break;
                case 4:
                    moveBackward();
                    stepsCounter++;
            }  
        }
        
        if(stepsCounter == 31)
            return false;
        else{
            return true;
        }
    }
    public int getCurrentRow(){
        return row;
    }
    
    public int getCurrentColumn(){
        return column;
    }
    
    public void moveForward(){
            row += 1;
            backTrackingRow[k] = row;
            backTrackingColumn[k] = column;
            k++;
    }
    
    public void moveRight(){
           column += 1;
           backTrackingRow[k] = row;
           backTrackingColumn[k] = column;
           k++;
    }
    public void moveLeft(){
           column -= 1;
           backTrackingRow[k] = row;
           backTrackingColumn[k] = column;
           k++;
    }
    
    public void moveBackward(){
            row -= 1;
            backTrackingRow[k] = row;
            backTrackingColumn[k] = column;
            k++;
    }
    
    public char whereAmI(int currentRow, int currentColumn){
        return currentLocation(currentRow, currentColumn);
    }
    
    public int nextStep(){
        if(whereAmI(row+1, column) == 'E'){
                endLabyrinth = true;
                return 1;
        }
        else if(whereAmI(row+1, column) == '0' && whereAmI(row+1, column) != '1')
            return 1;
        else if(whereAmI(row, column+1) == '0' && whereAmI(row, column+1) != '1')
            return 2;
        else if(whereAmI(row, column-1) == '0' && whereAmI(row, column-1) != '1')
            return 3;
        else if(whereAmI(row-1, column) == '0' && whereAmI(row-1, column) != '1')
            return 4;
        else{
            return 0;
        }
    }
    
    public void printTrajectory(){
        for(int i=0; i<=29; i++){
            //if(backTrackingRow[i] != 0 && backTrackingColumn[i] !=0)
                System.out.print(backTrackingRow[i] + "-" + backTrackingColumn[i]
                + " ");
        }
    }
}
