package arielcarvalhoassignment6;

import java.util.Random;

public class Labyrinth {
    private int row;
    private int column;
    private static char[][] labyrinth = new char[6][5];
    private static int[] previousCoordinateRow= new int[15];
    private static int[] previousCoordinateColumn= new int[15];
    
    public Labyrinth(){
    Random rand = new Random();
        int nextCell = rand.nextInt(3);
        boolean lastRow = false;
        int emptyCells = 0;
        row = 0;
        column = rand.nextInt(5);
        
        for(int i=0; i<=5; i++){    //Initialize all the cells with 1 (walls)
            for(int j=0; j<=4; j++)
                labyrinth[i][j] = '1';
        }
        
        labyrinth[0][column] = 'S'; //Start position cell
        
        int k = 1;
        
        previousCoordinateRow[0] = row;
        previousCoordinateColumn[0] = column;
        
        do{
           switch(nextCell){
               case 0:    //Forward case
                   if(row+1 == 5 && !lastRow){
                       lastRow = true;
                       labyrinth[row+1][column] = 'E';
                       emptyCells++;
                       break;
                   }
                   else if(lastRow){ //Back case
                       if(row-1 == 0){
                            row = previousCoordinateRow[k-1];
                            column = previousCoordinateColumn[k-1];
                            break;
                       }
                       else if(labyrinth[row-1][column] == '0'){
                            break;
                       }
                       else{
                            labyrinth[row-1][column] = '0';
                            row--;
                            previousCoordinateRow[k] = row;
                            previousCoordinateColumn[k] = column;
                            k++;
                            emptyCells++;
                            break;
                       }
                   }    
                   else{
                       labyrinth[row+1][column] = '0';
                       row++;
                       previousCoordinateRow[k] = row;
                       previousCoordinateColumn[k] = column;
                       k++;
                       emptyCells++;
                       break;
                   }
               case 1:    //Right case
                   if(column+1 > 4 || row == 0){ //Out of boundaries of labyrinth
                       row = previousCoordinateRow[k-1];
                       column = previousCoordinateColumn[k-1];
                       break;
                   }
                   else if(labyrinth[row][column+1] == '0'){ //Check if cell is already empty
                       break;
                   }
                   else{
                       labyrinth[row][column+1] = '0';
                       column++;
                       previousCoordinateRow[k] = row;
                       previousCoordinateColumn[k] = column;
                       k++;
                       emptyCells++;
                       break;
                   }
               case 2:    //Left case
                   if(column-1 < 0 || row == 0){ //Out of boundaries of labyrinth
                       row = previousCoordinateRow[k-1];
                       column = previousCoordinateColumn[k-1];
                       break;
                   }
                   else if(labyrinth[row][column-1] == '0'){ //Check if cell is already empty
                       break;
                   }
                   else{
                       labyrinth[row][column-1] = '0';
                       column--;
                       previousCoordinateRow[k] = row;
                       previousCoordinateColumn[k] = column;
                       k++;
                       emptyCells++;
                       break;
                   }
           }
          nextCell = rand.nextInt(3);
        }while(emptyCells <= 13);
    } 
    
    public void printMap(){
        for(int i=0; i<=5; i++){
            for(int j=0; j<=4; j++){
                System.out.print(labyrinth[i][j] + " ");
            }
            System.out.print("\n");
        }
    }
    
    public int startingPoint(char coordinate){ //This function returns the coordinate of starting point
        if (coordinate == 'r' || coordinate == 'R')
            return previousCoordinateRow[0];
        else{
            return previousCoordinateColumn[0];
        }
    }
    
    public char currentLocation(int x, int y){
        return labyrinth[x][y];
    }
}