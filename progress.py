import os

def count_asm_inline_in_c_files():
    results = []
    overall_lines = 0
    overall_matches = 0

    # Gather per-file stats
    for filename in os.listdir("."):
        if filename.endswith(".c"):
            with open(filename, "r", encoding="utf-8", errors="ignore") as f:
                lines = f.readlines()
                total_lines = len(lines)
                matches = sum(1 for line in lines if "ASM_INLINE" in line)

            # Inverted percentage: 0 matches = 100%, all lines matched = 0%
            percent = (1 - (matches / total_lines)) * 100 if total_lines > 0 else 100.0

            results.append((filename, matches, total_lines, percent))

            overall_lines += total_lines
            overall_matches += matches

    # Sort by percentage descending (most ASM_INLINE-free first)
    results.sort(key=lambda x: x[3], reverse=True)

    # Print header
    print(f"{'File':30} {'Matches':>8} {'Lines':>8} {'Free %':>8}")
    print("-" * 60)

    # Print per-file
    for filename, matches, total_lines, percent in results:
        print(f"{filename:30} {matches:8} {total_lines:8} {percent:7.2f}%")

    # Print totals (based on total lines across all files)
    print("-" * 60)
    overall_percent = (1 - (overall_matches / overall_lines)) * 100 if overall_lines > 0 else 100.0
    print(f"{'TOTAL (all .c files)':30} {overall_matches:8} {overall_lines:8} {overall_percent:7.2f}%")

if __name__ == "__main__":
    count_asm_inline_in_c_files()
