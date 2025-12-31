import calculator


def main() -> None:
    c = calculator.add(2, 3)
    d = calculator.sub(c, 1)
    assert d == 4


if __name__ == "__main__":
    main()
