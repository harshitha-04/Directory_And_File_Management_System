class File:
    def __init__(self, name, content):
        self.name = name
        self.content = content
        self.left = None
        self.right = None

class Directory:
    def __init__(self, name):
        self.name = name
        self.prev = None
        self.next = None
        self.files = None

def create_file(name, content):
    return File(name, content)

def add_file_to_directory(directory, new_file):
    def insert_file(root, file):
        if root is None:
            return file
        if file.name == root.name:
            print("File with the same name already exists in the current directory. Choose a different name.")
            return root
        elif file.name < root.name:
            root.left = insert_file(root.left, file)
        else:
            root.right = insert_file(root.right, file)
        return root

    directory.files = insert_file(directory.files, new_file)

def display_files(file):
    if file:
        display_files(file.left)
        print("File:", file.name)
        display_files(file.right)

def display_directory_contents(current_dir):
    temp = current_dir
    while temp:
        print("Directory:", temp.name)
        display_files(temp.files)
        temp = temp.next
    temp = current_dir.prev
    while temp:
        print("Directory:", temp.name)
        display_files(temp.files)
        temp = temp.prev

def delete_file_from_directory(directory, filename):
    def delete_node(root, name):
        if root is None:
            print("File not found.")
            return None

        if name < root.name:
            root.left = delete_node(root.left, name)
        elif name > root.name:
            root.right = delete_node(root.right, name)
        else:
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left

            min_larger_node = root.right
            while min_larger_node.left:
                min_larger_node = min_larger_node.left
            root.name, root.content = min_larger_node.name, min_larger_node.content
            root.right = delete_node(root.right, min_larger_node.name)
        return root

    directory.files = delete_node(directory.files, filename)

def delete_directory(directory):
    def free_files(file):
        if file:
            free_files(file.left)
            free_files(file.right)

    free_files(directory.files)
    if directory.next:
        delete_directory(directory.next)
    if directory.prev:
        directory.prev.next = directory.next
    if directory.next:
        directory.next.prev = directory.prev

def search_file(directory, filename):
    def search(file):
        if file is None:
            return None
        if filename == file.name:
            return file
        elif filename < file.name:
            return search(file.left)
        else:
            return search(file.right)

    temp = directory
    while temp:
        found = search(temp.files)
        if found:
            print(f"File found in directory '{temp.name}':")
            print("Name:", found.name)
            print("Content:", found.content.strip())
            return
        temp = temp.next
    print("File not found.")

def edit_file(file, content):
    if file:
        file.content = content

def show_file(directory, filename):
    file = directory.files
    stack = []
    found = None
    # Iterative in-order search
    while stack or file:
        while file:
            stack.append(file)
            file = file.left
        file = stack.pop()
        if file.name == filename:
            found = file
            break
        file = file.right
    if found:
        print(f"\n--- Contents of {found.name} ---")
        print(found.content.strip())
        print("--- End of file ---")
    else:
        print("File not found.")

def main():
    root = Directory("root")
    current_dir = root

    while True:
        print(f"\nCurrent Directory: {current_dir.name}")
        command = input("Enter command (createDir, createFile, listDir, changeDir, deleteFile, deleteDir, searchFile, editFile, showFile, quit): ")

        if command == "createDir":
            name = input("Enter directory name: ")
            new_dir = Directory(name)
            current_dir.next = new_dir
            new_dir.prev = current_dir
            current_dir = new_dir

        elif command == "createFile":
            name = input("Enter file name: ")
            content = input("Enter file content: ")
            new_file = create_file(name, content)
            add_file_to_directory(current_dir, new_file)

        elif command == "listDir":
            display_directory_contents(root)

        elif command == "changeDir":
            name = input("Enter directory name: ")
            temp = root
            found = False
            while temp:
                if temp.name == name:
                    current_dir = temp
                    found = True
                    break
                temp = temp.next
            if not found:
                print("Directory not found.")

        elif command == "deleteFile":
            name = input("Enter file name: ")
            delete_file_from_directory(current_dir, name)

        elif command == "deleteDir":
            prev_dir = current_dir.prev
            delete_directory(current_dir)
            current_dir = prev_dir if prev_dir else root

        elif command == "searchFile":
            name = input("Enter file name: ")
            search_file(current_dir, name)

        elif command == "editFile":
            name = input("Enter file name: ")
            file = current_dir.files
            stack = []
            found = None
            # Iterative in-order search
            while stack or file:
                while file:
                    stack.append(file)
                    file = file.left
                file = stack.pop()
                if file.name == name:
                    found = file
                    break
                file = file.right
            if found:
                content = input("Enter new content: ")
                edit_file(found, content)
                print("File content updated successfully.")
            else:
                print("File not found.")

        elif command == "showFile":
            name = input("Enter file name: ")
            show_file(current_dir, name)

        elif command == "quit":
            break

        else:
            print("Invalid command.")

    delete_directory(root)

if __name__ == "__main__":
    main()
