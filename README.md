# ExchangeSim

A simulated exchange. Users start with a custom USD balance and trade crypto pairs against live market data.

## MVP

Paper trading. Orders fill at the live market price, so there's no matching engine yet.

- Market feed handler that ingests one crypto feed into TimescaleDB
- Ledger database for user accounts, balances, orders and fills
- Spring Boot backend for placing orders and tracking positions
- React + TypeScript frontend for viewing prices, placing trades and seeing your portfolio
- Every pair is quoted in USD (`X/USD`)

## Later

- C++ in-memory matching engine (LMAX-style)
- Tickerplant and multiple feeds

## Layout

| Directory   | Contents                          |
|-------------|-----------------------------------|
| `backend/`  | Spring Boot API                   |
| `frontend/` | React app                         |
| `mdp/`      | Market Data Platform (C++)        |
| `engine/`   | Matching Engine (C++) (not started)     |
| `_postgres` | Schemas for ledger and market data |

## Status

Early. Currently focused on market data injestion.