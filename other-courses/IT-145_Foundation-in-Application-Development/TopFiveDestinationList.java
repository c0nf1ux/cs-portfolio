import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;

public class TopFiveDestinationList {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                TopDestinationListFrame topDestinationListFrame = new TopDestinationListFrame();
                topDestinationListFrame.setTitle("Top 5 Destination List");
                topDestinationListFrame.setVisible(true);
            }
        });
    }
}

class TopDestinationListFrame extends JFrame {
    private DefaultListModel listModel;

    public TopDestinationListFrame() {
        super("Top Five Destination List");

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setSize(900, 750);

        listModel = new DefaultListModel();

        // Updated top 5 list with new destinations and images
        addDestinationNameAndPicture("1. New York City, USA - The city that never sleeps, bustling with energy and iconic sights", new ImageIcon(getClass().getResource("/resources/nyc.jpg")));
        addDestinationNameAndPicture("2. Rome, Italy - Eternal city with ancient wonders and vibrant modern life", new ImageIcon(getClass().getResource("/resources/rome.jpg")));
        addDestinationNameAndPicture("3. Bali, Indonesia - Tropical paradise with stunning beaches, lush landscapes, and vibrant culture", new ImageIcon(getClass().getResource("/resources/bali.jpg")));
        addDestinationNameAndPicture("4. Tokyo, Japan - A captivating blend of ultramodern and traditional, with cherry blossoms and vibrant street life", new ImageIcon(getClass().getResource("/resources/tokyo.jpg")));
        addDestinationNameAndPicture("5. Paris, France - City of Love, offering romantic views, iconic landmarks, and unforgettable experiences", new ImageIcon(getClass().getResource("/resources/paris.jpg")));
        
        JList list = new JList(listModel);
        JScrollPane scrollPane = new JScrollPane(list);

        TextAndIconListCellRenderer renderer = new TextAndIconListCellRenderer(2);

        list.setCellRenderer(renderer);

        getContentPane().add(scrollPane, BorderLayout.CENTER);
        
        // Add your name label
        JLabel nameLabel = new JLabel("Created by Heath Davis - 9/22/2024");
        nameLabel.setHorizontalAlignment(JLabel.CENTER);
        getContentPane().add(nameLabel, BorderLayout.SOUTH);
    }

    private void addDestinationNameAndPicture(String text, Icon icon) {
        TextAndIcon tai = new TextAndIcon(text, icon);
        listModel.addElement(tai);
    }
}

// The rest of the classes (TextAndIcon and TextAndIconListCellRenderer) remain unchanged