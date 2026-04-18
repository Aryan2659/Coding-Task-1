# OrderBook

Aggregated limit-order book in C++17. Handles `new`, `change`, and `cancel` events; prints buys high→low and sells low→high, with quantities summed per price level.

## Build

```bash
g++ -std=c++17 -O2 order_book.cpp -o order_book && ./order_book
```

## Design

- `unordered_map<id, Order>` — O(1) lookup for change/cancel.
- Two `map<price, qty>` — one per side, already sorted for `Print`.
- Levels are erased when they hit zero qty, so no phantom rows.
- Aggregates use `uint64_t` to avoid overflow.

Event handlers are O(log L), `Print` is O(L), where L = price levels per side.

## Notes

- Duplicate `order_id` on new → ignored.
- Unknown id on change/cancel → ignored (no throw).

## Tests

`main()` runs the spec example plus edge cases (duplicate ids, cancelling the last order at a level, unknown-id operations).
