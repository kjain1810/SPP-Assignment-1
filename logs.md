# Runtime logs

| Optimisation      | Runtime | Cache misses |
| ----------------- | ------- | ------------ |
| Swap loops        | 26      | 5.2%         |
| Dynamic 2D arrays | 11.05   | 7.8%         |
| Static 2D arrays  | slow    |              |
| Static 1D arrays  | 11.2    | 7.7%         |
| Dynamic 1D arrays | 11.1    |              |

## Notes

1. Freeing memory helps runtime, probably because it reduces cache misses