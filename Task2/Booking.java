
import java.io.Serializable;

public class Booking implements Serializable {
    private String guestName;
    private int roomNumber;
    private String category;
    private String paymentStatus;

    public Booking(String guestName, int roomNumber, String category, String paymentStatus) {
        this.guestName = guestName;
        this.roomNumber = roomNumber;
        this.category = category;
        this.paymentStatus = paymentStatus;
    }

    public int getRoomNumber() { return roomNumber; }

    @Override
    public String toString() {
        return "Booking Details:\nGuest: " + guestName +
               "\nRoom: " + roomNumber +
               "\nCategory: " + category +
               "\nPayment: " + paymentStatus;
    }
}
