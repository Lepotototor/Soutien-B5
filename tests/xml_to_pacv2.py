import xml.etree.ElementTree as ET
import sys

if len(sys.argv) != 3:
    print("Usage: python convert_criterion_to_pacv2.py input.xml output.xml")
    sys.exit(1)

input_file, output_file = sys.argv[1], sys.argv[2]

tree = ET.parse(input_file)
root = tree.getroot()

out_root = ET.Element("testsuites")
out_suite = ET.SubElement(out_root, "testsuite")

for suite in root.findall("testsuite"):
    for case in suite.findall("testcase"):
        name = case.get("name", "unknown")
        status = case.get("status", "")
        classname = suite.get("name", "exercise.tests")

        out_case = ET.SubElement(out_suite, "testcase", {
            "name": name,
            "classname": classname,
            "time": case.get("time", "0.0"),
            "zluor_idx": "0"
        })

        if status != "PASSED":
            failure = ET.SubElement(out_case, "failure")
            failure.text = f"Test {name} failed in suite {classname}"

tree_out = ET.ElementTree(out_root)
ET.indent(tree_out, space="  ")
tree_out.write(output_file, encoding="UTF-8", xml_declaration=True)
