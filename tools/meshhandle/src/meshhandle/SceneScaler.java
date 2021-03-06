package meshhandle;

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.xml.parsers.ParserConfigurationException;
import meshhandle.io.xml.scene.SceneFormat2Loader;
import meshhandle.io.xml.scene.SceneFormat2Writer;
import meshhandle.model.scene.Scene;
import org.xml.sax.SAXException;

public class SceneScaler {

    /**
     * @param args
     * @throws IOException
     * @throws ParserConfigurationException
     * @throws SAXException
     */
    public static void main(String[] args) throws IOException, SAXException,
            ParserConfigurationException {

        String inputFile;
        float factor;
        String outputFile;

        if (args.length < 3) {
            BufferedReader reader = new BufferedReader(new InputStreamReader(
                    System.in));

            System.out.print("Input-Scene  :");
            inputFile = reader.readLine();
            System.out.print("Faktor          :");
            factor = Float.parseFloat(reader.readLine());
            System.out.print("Output-Scene :");
            outputFile = reader.readLine();
        } else {
            inputFile = args[0];
            factor = Float.parseFloat(args[1]);
            outputFile = args[2];
        }

        System.out.println("processing " + inputFile);
        Scene scene = new SceneFormat2Loader().readScene(inputFile);
        scene.scale(factor);
        FileWriter outFile = new FileWriter(outputFile, false);
        new SceneFormat2Writer(outFile).write(scene);
        outFile.flush();
    }
}
