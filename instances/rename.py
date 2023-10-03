import os

def rename_subdirectories(folder_path):
    count = 1

    for subdir in os.listdir(folder_path):
        subdir_path = os.path.join(folder_path, subdir)

        if os.path.isdir(subdir_path) and "-" in subdir:
            new_name = f"instances{count}"
            new_subdir_path = os.path.join(folder_path, new_name)

            os.rename(subdir_path, new_subdir_path)
            print(f"Renamed '{subdir}' to '{new_name}'")

            count += 1

if __name__ == "__main__":
    folder_path = "."  # Replace with the actual folder path
    rename_subdirectories(folder_path)