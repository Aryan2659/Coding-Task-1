# OrderBook

Aggregated limit-order book in C++17. Handles `new`, `change`, and `cancel` events; prints buys high→low and sells low→high, with quantities summed per price level.



## Notes

- Duplicate `order_id` on new → ignored.
- Unknown id on change/cancel → ignored (no throw).

## Tests

`main()` runs the spec example plus edge cases (duplicate ids, cancelling the last order at a level, unknown-id operations).
