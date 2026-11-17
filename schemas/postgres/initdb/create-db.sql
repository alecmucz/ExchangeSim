CREATE DATABASE exchangesim_ledger;
CREATE DATABASE exchangesim_marketdata;

\connect exchangesim_marketdata
CREATE EXTENSION IF NOT EXISTS timescaledb;