import sys
import antigravity


def geohashing():
    """
    Example usage:
    $ python3 geohashing.py 37.421542 -122.085589 2005-05-26 10458.68
    """
    try:
        if len(sys.argv) != 5:
            raise ValueError("Usage: python3 geohashing.py <latitude> <longitude> <date> <dow_jones_value>")
        
        latitude = float(sys.argv[1])
        longitude = float(sys.argv[2])
        date = sys.argv[3].encode('utf-8')
        dow_jones = sys.argv[4].encode('utf-8')

        antigravity.geohash(latitude, longitude, date + b'-' + dow_jones)
        
    except (ValueError, IndexError) as e:
        print(f"Error: Invalid arguments. {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    geohashing()
