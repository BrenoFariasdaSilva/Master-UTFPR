package edu.utfpr;

import java.util.Calendar;

public class Main {
    private static final String[] MONTHS = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    private static final int[][] DAYS_IN_MONTH = {
        { 0,31,28,31,30,31,30,31,31,30,31,30,31 },
        { 0,31,29,31,30,31,30,31,31,30,31,30,31 }
    };

    public static String cal(int month, int year) {
        StringBuilder sb = new StringBuilder();

        int leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0;
        int daysInMonth = DAYS_IN_MONTH[leap][month];
        
        int displayMonth = month;
        if (month < 3) {
            month += 12;
            year--;
        }

        int k = year % 100;
        int j = year / 100;
        int d = 1;
        int h = (d + 13*(month + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
        int firstDay = (h + 6) % 7;
        int weekDay = firstDay;

        sb.append(String.format("   %s %d\n", MONTHS[displayMonth], (month > 12 ? year + 1 : year)));
        sb.append("Su Mo Tu We Th Fr Sa\n");

        for (int i = 0; i < firstDay; i++) {
            sb.append("   ");
        }

        for (int day = 1; day <= daysInMonth; day++) {
            sb.append(String.format("%2d", day));
            weekDay++;
            if (weekDay > 6) {
                weekDay = 0;
                sb.append("\n");
            } else {
                sb.append(" ");
            }
        }

        if (weekDay != 0) {
            sb.append("\n");
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        int month, year;

        if (args.length == 0) {
            Calendar now = Calendar.getInstance();
            month = now.get(Calendar.MONTH) + 1;
            year = now.get(Calendar.YEAR);
            System.out.print(cal(month, year));
        } else if (args.length == 1) {
            year = Integer.parseInt(args[0]);
            for (month = 1; month <= 12; month++) {
                System.out.println(cal(month, year));
            }
        } else if (args.length == 2) {
            month = Integer.parseInt(args[0]);
            year = Integer.parseInt(args[1]);
            System.out.print(cal(month, year));
        } else {
            System.err.println("Usage: java Main [month] year");
        }
    }
}
