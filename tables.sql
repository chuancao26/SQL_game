create database prueba;
use prueba;
-- Crear las tablas
CREATE TABLE producto (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    descripcion TEXT,
    precio FLOAT NOT NULL
);

CREATE TABLE orden (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    amount FLOAT NOT NULL,
    date VARCHAR(20) NOT NULL
);

CREATE TABLE persona (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL,
    apellidos VARCHAR(100) NOT NULL,
    dni VARCHAR(20) NOT NULL UNIQUE
);

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    age INT NOT NULL
);

-- Insertar datos en la tabla producto
INSERT INTO producto (nombre, descripcion, precio) VALUES
('Laptop', 'Portátil de última generación', 999.99),
('Smartphone', 'Teléfono inteligente con cámara de alta resolución', 599.99),
('Auriculares', 'Auriculares inalámbricos con cancelación de ruido', 199.99),
('Tablet', 'Tablet ligera y potente', 399.99),
('Monitor', 'Monitor 4K de 27 pulgadas', 349.99);

-- Insertar datos en la tabla orden
INSERT INTO orden (user_id, amount, date) VALUES
(1, 1299.99, '2024-07-14'),
(2, 599.99, '2024-07-13'),
(3, 949.98, '2024-07-12'),
(4, 399.99, '2024-07-11'),
(5, 549.98, '2024-07-10');

-- Insertar datos en la tabla persona
INSERT INTO persona (nombre, apellidos, dni) VALUES
('Juan', 'Pérez García', '12345678A'),
('María', 'López Rodríguez', '87654321B'),
('Carlos', 'González Fernández', '11223344C'),
('Ana', 'Martínez Sánchez', '44332211D'),
('Pedro', 'Ruiz Gómez', '55667788E');

-- Insertar datos en la tabla users
INSERT INTO users (name, age) VALUES
('Alice Johnson', 28),
('Bob Smith', 35),
('Charlie Brown', 42),
('Diana Davis', 31),
('Eric Wilson', 39);
