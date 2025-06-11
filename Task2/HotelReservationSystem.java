import java.io.*;
import java.util.*;

public class HotelReservationSystem {
    private static final String ROOMS_FILE = "rooms.dat";
    private static final String BOOKINGS_FILE = "bookings.dat";

    private static ArrayList<Room> rooms = new ArrayList<>();
    private static ArrayList<Booking> bookings = new ArrayList<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        loadRooms();
        loadBookings();
        menu();
        saveRooms();
        saveBookings();
    }

    private static void menu() {
        int choice;
        do {
            System.out.println("\n=== Hotel Reservation System ===");
            System.out.println("1. View Available Rooms");
            System.out.println("2. Make a Reservation");
            System.out.println("3. Cancel a Reservation");
            System.out.println("4. View All Bookings");
            System.out.println("5. Exit");
            System.out.print("Choose an option: ");
            choice = scanner.nextInt();

            switch (choice) {
                case 1 -> viewAvailableRooms();
                case 2 -> makeReservation();
                case 3 -> cancelReservation();
                case 4 -> viewAllBookings();
                case 5 -> System.out.println("Thank you for using the system.");
                default -> System.out.println("Invalid choice.");
            }
        } while (choice != 5);
    }

    private static void viewAvailableRooms() {
        System.out.println("\nAvailable Rooms:");
        for (Room r : rooms) {
            if (!r.isBooked())
                System.out.println(r);
        }
    }

    private static void makeReservation() {
        scanner.nextLine(); // clear newline
        System.out.print("Enter your name: ");
        String name = scanner.nextLine();

        viewAvailableRooms();

        System.out.print("Enter room number to book: ");
        int roomNumber = scanner.nextInt();

        for (Room r : rooms) {
            if (r.getRoomNumber() == roomNumber && !r.isBooked()) {
                r.book();
                System.out.println("Simulating payment...");
                String paymentStatus = "Paid";
                Booking b = new Booking(name, r.getRoomNumber(), r.getCategory(), paymentStatus);
                bookings.add(b);
                System.out.println("Booking Successful!");
                return;
            }
        }
        System.out.println("Room not available or does not exist.");
    }

    private static void cancelReservation() {
        System.out.print("Enter room number to cancel: ");
        int roomNumber = scanner.nextInt();
        Booking toRemove = null;

        for (Booking b : bookings) {
            if (b.getRoomNumber() == roomNumber) {
                toRemove = b;
                break;
            }
        }

        if (toRemove != null) {
            bookings.remove(toRemove);
            for (Room r : rooms) {
                if (r.getRoomNumber() == roomNumber) {
                    r.cancel();
                    break;
                }
            }
            System.out.println("Reservation cancelled.");
        } else {
            System.out.println("No such booking found.");
        }
    }

    private static void viewAllBookings() {
        if (bookings.isEmpty()) {
            System.out.println("No bookings yet.");
        } else {
            for (Booking b : bookings) {
                System.out.println("\n" + b);
            }
        }
    }

    private static void loadRooms() {
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(ROOMS_FILE))) {
            rooms = (ArrayList<Room>) in.readObject();
        } catch (Exception e) {
            initializeRooms();
        }
    }

    private static void saveRooms() {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(ROOMS_FILE))) {
            out.writeObject(rooms);
        } catch (IOException e) {
            System.out.println("Error saving rooms.");
        }
    }

    private static void loadBookings() {
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(BOOKINGS_FILE))) {
            bookings = (ArrayList<Booking>) in.readObject();
        } catch (Exception e) {
            bookings = new ArrayList<>();
        }
    }

    private static void saveBookings() {
        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(BOOKINGS_FILE))) {
            out.writeObject(bookings);
        } catch (IOException e) {
            System.out.println("Error saving bookings.");
        }
    }

    private static void initializeRooms() {
        rooms.add(new Room(101, "Standard"));
        rooms.add(new Room(102, "Standard"));
        rooms.add(new Room(201, "Deluxe"));
        rooms.add(new Room(202, "Deluxe"));
        rooms.add(new Room(301, "Suite"));
        rooms.add(new Room(302, "Suite"));
    }
}
