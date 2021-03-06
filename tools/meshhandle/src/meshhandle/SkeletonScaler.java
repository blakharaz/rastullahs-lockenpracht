package meshhandle;

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.xml.parsers.ParserConfigurationException;

import meshhandle.io.xml.SkeletonLoader;
import meshhandle.model.skeleton.Skeleton;

import org.xml.sax.SAXException;

public class SkeletonScaler {

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

            System.out.print("Input-Skeleton  :");
            inputFile = reader.readLine();
            System.out.print("Faktor          :");
            factor = Float.parseFloat(reader.readLine());
            System.out.print("Output-Skeleton :");
            outputFile = reader.readLine();
        } else {
            inputFile = args[0];
            factor = Float.parseFloat(args[1]);
            outputFile = args[2];
        }

        System.out.println("processing " + inputFile);
        Skeleton skel = new SkeletonLoader().readSkeleton(inputFile);
        skel.scale(factor);
        FileWriter outFile = new FileWriter(outputFile, false);
        outFile.write(skel.toXML());
        outFile.flush();
    }
}
