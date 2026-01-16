from path import Path


def main():
    try:
        directory = Path('my_folder')

        if not directory.exists():
            directory.mkdir()
            print(f"Created directory: {directory}")
        else:
            print(f"Directory already exists: {directory}")

        file_path = directory / 'my_file.txt'

        content = "Hello from 42 Piscine Django!\nThis is a test file created with path.py library.\n"
        file_path.write_text(content)
        print(f"Written to file: {file_path}")

        read_content = file_path.read_text()
        print(f"\nContent of {file_path}:")
        print(read_content)
        
    except Exception as e:
        print(f"Error: {e}")
        return


if __name__ == '__main__':
    main()
