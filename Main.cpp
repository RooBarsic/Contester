
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.io.File;

public class Main {
    private final String programmsDirectory = "cpp-programms";
    private final String testsDirectory = "test-pack";
    private final String testInputDirectory = "input";
    private final String testOutputDirectory = "output";
    private final String standardInputFileName = "input.txt";
    private final String standardOutputFileName = "output.txt";
    private final String standardResultFileName = "result.txt";

    public static void main(String[] args) {
        String projectName = "sum-ab";

        System.out.println("Hello Fara!");

        Main main = new Main();
        main.startTesting(projectName, 3);
    }

    public void showRes(){
        try(Scanner programmAnswerScanner = new Scanner(new File(standardOutputFileName));
            Scanner testAnswerScanner = new Scanner(new File(standardResultFileName))){
            System.out.println(" -------- programm ---------- ");
            while((programmAnswerScanner.hasNextLine())){
                System.out.println(programmAnswerScanner.nextLine());
            }
            System.out.println(" ----- test ----- ");
            while(testAnswerScanner.hasNextLine()){
                System.out.println(testAnswerScanner.nextLine());
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void startTesting(String projectName, int numberOfTest){
        if(numberOfTest == -1){

        }
        int testsPassedNum = 0;
        for(int i = 1; i <= numberOfTest; i++){
            updateTestEnvironment(i, projectName);
            runProject(projectName);
            //showRes();
            if(checkResult()){
                testsPassedNum++;
                System.out.println(" ~~~ log test " + i + " : " + " OK ");
            }
            else {
                System.out.println(" ~~~ log test " + i + " : " + " ERROR ");
            }
        }
        System.out.println(" ~~~ result : tests ( passed / failed ) : " + testsPassedNum + " / " + (numberOfTest - testsPassedNum));
        System.out.println("");
    }

    public boolean checkResult(){
        try(Scanner programmAnswerScanner = new Scanner(new File(standardOutputFileName));
            Scanner testAnswerScanner = new Scanner(new File(standardResultFileName))){
            while((programmAnswerScanner.hasNextLine()) && (testAnswerScanner.hasNextLine())){
                final String testResultRow = testAnswerScanner.nextLine();
                final String programmResultRow = programmAnswerScanner.nextLine();
                if(!testResultRow.equals(programmResultRow)){
                    return false;
                }
            }
            if((testAnswerScanner.hasNextLine())){
                return false;
            }
            return true;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean runProject(String projectName){
        try {
            String pathToMainFile = programmsDirectory + "/" + projectName + "/" + "main.cpp";
            Process compilingProcess = Runtime.getRuntime().exec(" g++ " + pathToMainFile);
            while (compilingProcess.isAlive()){

            }
            Process runInTest = Runtime.getRuntime().exec(" ./a.out");
            while (runInTest.isAlive()){

            }
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean updateTestEnvironment(int testId, String projectName){
        String sourceTestInputDataPath = testsDirectory + "/" + projectName + "/" + testInputDirectory + "/test-" + testId + "-in.txt";
        String sourceTestResultDataPath = testsDirectory + "/" + projectName + "/" + testOutputDirectory + "/test-" + testId + "-out.txt";
        try(Scanner testInputDataScanner = new Scanner(new File(sourceTestInputDataPath));
            PrintWriter inputDataWriter = new PrintWriter(new File(standardInputFileName));
            Scanner testResultDataScanner = new Scanner(new File(sourceTestResultDataPath));
            PrintWriter resultDataWriter = new PrintWriter(new File(standardResultFileName));
            PrintWriter programmResultFileWriter = new PrintWriter(new File(standardOutputFileName))
            ){
                while(testInputDataScanner.hasNextLine()){
                    inputDataWriter.println(testInputDataScanner.nextLine());
                    inputDataWriter.flush();
                }
                while(testResultDataScanner.hasNextLine()){
                    resultDataWriter.println(testResultDataScanner.nextLine());
                    resultDataWriter.flush();
                }
                programmResultFileWriter.print("");
                programmResultFileWriter.flush();
                return true;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return false;
        }
    }
}
