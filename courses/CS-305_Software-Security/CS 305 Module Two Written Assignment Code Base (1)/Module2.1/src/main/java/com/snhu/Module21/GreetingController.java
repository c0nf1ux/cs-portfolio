package com.snhu.Module21;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.concurrent.atomic.AtomicLong;

@RestController
public class GreetingController {
	private static final String template = "Hello, %s!";
	private final AtomicLong counter = new AtomicLong();

	@GetMapping("/greeting")
	public ResponseEntity<Greeting> greeting(@RequestParam String name) {
		String sanitizedName = name.replaceAll("[^a-zA-Z0-9 ]", "");
		return ResponseEntity.ok(
				new Greeting(counter.incrementAndGet(), String.format(template, sanitizedName))
		);
	}

	@GetMapping("/number/{id}")
	public ResponseEntity<Greeting> number(@PathVariable int id) {
		int[] myArray = {897, 56, 78, 90, 12, 123, 75};
		if (id < 0 || id >= myArray.length) {
			return ResponseEntity.badRequest().build();
		}
		return ResponseEntity.ok(
				new Greeting(counter.incrementAndGet(), "Element: " + myArray[id])
		);
	}
}