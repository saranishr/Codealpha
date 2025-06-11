import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

class Student {
    private final String name;
    private final double marksObtained;
    private final double totalMarks;

    public Student(String name, double marksObtained, double totalMarks) {
        this.name = name;
        this.marksObtained = marksObtained;
        this.totalMarks = totalMarks;
    }

    public String getName() {
        return name;
    }

    public double getMarksObtained() {
        return marksObtained;
    }

    public double getTotalMarks() {
        return totalMarks;
    }

    public double getPercentage() {
        return (marksObtained / totalMarks) * 100;
    }

    public String getGrade() {
        double percent = getPercentage();
        if (percent >= 90) return "A";
        if (percent >= 80) return "B";
        if (percent >= 70) return "C";
        if (percent >= 60) return "D";
        return "F";
    }
}

public class Main {
    private final ArrayList<Student> students = new ArrayList<>();
    private final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        while (true) {
            switch (menuChoice()) {
                case 1 -> addStudents();
                case 2 -> displaySummaryReport();
                case 3 -> searchStudentByName();
                case 4 -> {
                    System.out.println("Thank you! Exiting...");
                    return;
                }
                default -> System.out.println("Invalid choice. Try again.");
            }
        }
    }

    private int menuChoice() {
        System.out.println("\n=== Student Grade Tracker ===");
        System.out.println("1. Add Students");
        System.out.println("2. Display Summary Report");
        System.out.println("3. Search Student by Name");
        System.out.println("4. Exit");
        System.out.print("Select an option: ");
        try {
            return scanner.nextInt();
        } catch (InputMismatchException e) {
            scanner.nextLine(); // clear buffer
            return -1;
        }
    }

    private void addStudents() {
        System.out.print("How many students to add? ");
        int count = readInt();
        for (int i = 1; i <= count; i++) {
            System.out.print("Enter name of student #" + i + ": ");
            String name = scanner.next();
            System.out.print("Enter marks obtained by " + name + ": ");
            double marksObtained = readDouble(0, 1000);
            System.out.print("Enter total marks for " + name + ": ");
            double totalMarks = readDouble(marksObtained, 1000);
            students.add(new Student(name, marksObtained, totalMarks));
        }
        System.out.println(count + " student(s) added.");
    }

    private void displaySummaryReport() {
        if (students.isEmpty()) {
            System.out.println("No data available. Please add students first.");
            return;
        }

        double totalPercentage = 0;
        Student top = null, bottom = null;

        for (Student s : students) {
            double percent = s.getPercentage();
            totalPercentage += percent;
            if (top == null || percent > top.getPercentage()) top = s;
            if (bottom == null || percent < bottom.getPercentage()) bottom = s;
        }

        double averagePercentage = totalPercentage / students.size();

        System.out.println("\n--- Summary Report ---");
        System.out.printf("Total Students : %d%n", students.size());
        System.out.printf("Average %%       : %.2f%%%n", averagePercentage);
        System.out.printf("Top Scorer     : %s (%.2f%%, Grade: %s)%n", top.getName(), top.getPercentage(), top.getGrade());
        System.out.printf("Lowest Scorer  : %s (%.2f%%, Grade: %s)%n", bottom.getName(), bottom.getPercentage(), bottom.getGrade());

        System.out.println("\nAll Students:");
        System.out.printf("%-15s %-10s %-10s %-10s %-6s%n", "Name", "Obtained", "Total", "Percent", "Grade");
        System.out.println("-------------------------------------------------------------");
        for (Student s : students) {
            System.out.printf("%-15s %-10.2f %-10.2f %-9.2f %-6s%n",
                    s.getName(), s.getMarksObtained(), s.getTotalMarks(), s.getPercentage(), s.getGrade());
        }
    }

    private void searchStudentByName() {
        if (students.isEmpty()) {
            System.out.println("No data available. Please add students first.");
            return;
        }
        System.out.print("Enter student name to search: ");
        String searchName = scanner.next();
        boolean found = false;

        for (Student s : students) {
            if (s.getName().equalsIgnoreCase(searchName)) {
                System.out.printf("Student: %s%nMarks: %.2f/%.2f%nPercentage: %.2f%%%nGrade: %s%n",
                        s.getName(), s.getMarksObtained(), s.getTotalMarks(),
                        s.getPercentage(), s.getGrade());
                found = true;
            }
        }

        if (!found) {
            System.out.println("No student found with that name.");
        }
    }

    private int readInt() {
        while (true) {
            try {
                int n = scanner.nextInt();
                if (n < 0) throw new InputMismatchException();
                return n;
            } catch (InputMismatchException e) {
                System.out.print("Enter a valid non-negative number: ");
                scanner.nextLine();
            }
        }
    }

    private double readDouble(double min, double max) {
        while (true) {
            try {
                double d = scanner.nextDouble();
                if (d < min || d > max) throw new InputMismatchException();
                return d;
            } catch (InputMismatchException e) {
                System.out.printf("Enter a number between %.2f and %.2f: ", min, max);
                scanner.nextLine();
            }
        }
    }
}
