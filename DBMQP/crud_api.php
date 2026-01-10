<?php
// Database connection
$conn = new mysqli("localhost", "root", "", "company");

if ($conn->connect_error) {
    die(json_encode(['success' => false, 'message' => 'Connection failed']));
}

$action = $_GET['action'];

// VIEW
if ($action == 'view') {
    $result = $conn->query("SELECT * FROM dept");
    $data = [];
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }
    echo json_encode($data);
}

// INSERT
if ($action == 'insert') {
    $data = json_decode(file_get_contents('php://input'), true);
    $deptno = $data['deptno'];
    $dname = $data['dname'];
    $location = $data['location'];
    
    $sql = "INSERT INTO dept (deptno, dname, location) VALUES ('$deptno', '$dname', '$location')";
    
    if ($conn->query($sql) === TRUE) {
        echo json_encode(['success' => true, 'message' => 'Department inserted successfully!']);
    } else {
        echo json_encode(['success' => false, 'message' => 'Error: ' . $conn->error]);
    }
}

// UPDATE
if ($action == 'update') {
    $data = json_decode(file_get_contents('php://input'), true);
    $deptno = $data['deptno'];
    $dname = $data['dname'];
    $location = $data['location'];
    
    $sql = "UPDATE dept SET dname='$dname', location='$location' WHERE deptno='$deptno'";
    
    if ($conn->query($sql) === TRUE) {
        echo json_encode(['success' => true, 'message' => 'Department updated successfully!']);
    } else {
        echo json_encode(['success' => false, 'message' => 'Error: ' . $conn->error]);
    }
}

// DELETE
if ($action == 'delete') {
    $data = json_decode(file_get_contents('php://input'), true);
    $deptno = $data['deptno'];
    
    $sql = "DELETE FROM dept WHERE deptno='$deptno'";
    
    if ($conn->query($sql) === TRUE) {
        echo json_encode(['success' => true, 'message' => 'Department deleted successfully!']);
    } else {
        echo json_encode(['success' => false, 'message' => 'Error: ' . $conn->error]);
    }
}

$conn->close();
?>