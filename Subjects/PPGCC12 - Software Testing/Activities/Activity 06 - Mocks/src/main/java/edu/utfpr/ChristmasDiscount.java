package edu.utfpr.bookstore;

import java.time.LocalDate;
import java.time.Month;

public class ChristmasDiscount {
	private final Clock clock;

	public ChristmasDiscount(Clock clock) {
		this.clock = clock;
	}

	public double applyDiscount(double amount) {
		LocalDate today = clock.now();

		if (today.getMonth() == Month.DECEMBER && today.getDayOfMonth() == 25) {
			return amount * 0.85;
		}
		return amount;
	}
}
