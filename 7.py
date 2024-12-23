class Student:
    def __init__(self, name, grades):
        self.name = name
        self.grades = grades  # список оценок

    def add_grades(self, grades):
        """Добавить оценки для ученика."""
        self.grades.extend(grades)

    def remove_grades(self, index):
        """Удалить оценку по индексу."""
        if 0 <= index < len(self.grades):
            self.grades.pop(index)
        else:
            print("Некорректный индекс оценки!")

    def update_grade(self, index, new_grade):
        """Изменить оценку ученика по индексу."""
        if 0 <= index < len(self.grades):
            self.grades[index] = new_grade
        else:
            print("Некорректный индекс оценки!")

    def calculate_final_grade(self):
        """Посчитать итоговую оценку ученика (среднее значение всех оценок)."""
        if not self.grades:
            return 0
        return sum(self.grades) / len(self.grades)

    def __str__(self):
        return f"{self.name} {self.grades}"

class StudentDatabase:
    def __init__(self):
        self.students = []

    def add_student(self, name, grades):
        """Добавить нового ученика."""
        self.students.append(Student(name, grades))

    def find_student(self, name):
        """Найти ученика по имени."""
        for student in self.students:
            if student.name == name:
                return student
        return None

    def remove_student(self, name):
        """Удалить ученика по имени."""
        student = self.find_student(name)
        if student:
            self.students.remove(student)
        else:
            print("Ученик не найден!")

    def save_to_file(self, file_path):
        """Сохранить данные в файл в формате текстового файла."""
        with open(file_path, 'w', encoding='utf-8') as file:
            for student in self.students:
                file.write(f"{student.name} {' '.join(map(str, student.grades))}\n")

    def load_from_file(self, file_path):
        """Загрузить данные из файла в формате текстового файла."""
        try:
            with open(file_path, 'r', encoding='utf-8') as file:
                for line in file:
                    parts = line.strip().split()
                    name = ' '.join(parts[:-4])  # Имя ученика (все слова, кроме последних 4 частей)
                    grades = list(map(int, parts[-4:]))  # Оценки ученика (последние 4 части)
                    self.add_student(name, grades)
        except FileNotFoundError:
            print("Файл не найден, начинаем с пустой базы данных.")
        except Exception as e:
            print(f"Ошибка при загрузке файла: {e}")

# Основное меню с улучшенным интерфейсом
def main():
    # Запрашиваем у пользователя путь к файлу
    file_path = input("Введите путь к файлу с данными об учениках (например, students.txt): ")

    db = StudentDatabase()

    # Загружаем данные из файла при запуске
    db.load_from_file(file_path)

    while True:
        print("\n==================== Меню ====================")
        print("1. Добавить ученика")
        print("2. Добавить оценки ученику")
        print("3. Удалить ученика")
        print("4. Удалить оценку ученика")
        print("5. Изменить оценку ученика")
        print("6. Посчитать итоговую оценку ученика")
        print("7. Посчитать итоговую оценку всех учеников")
        print("8. Сохранить и выйти")
        print("9. Выйти без сохранения")
        print("=============================================")
        
        choice = input("Выберите действие (1-9): ")

        if choice == '1':
            name = input("\nВведите имя ученика (например, Иванов А. А.): ")
            grades = list(map(int, input("Введите оценки через пробел (например, 4 3 5 4): ").split()))
            db.add_student(name, grades)
            print(f"Ученик {name} добавлен!")

        elif choice == '2':
            name = input("\nВведите имя ученика для добавления оценок: ")
            student = db.find_student(name)
            if student:
                grades = list(map(int, input("Введите новые оценки через пробел: ").split()))
                student.add_grades(grades)
                print(f"Оценки {grades} добавлены ученику {name}.")
            else:
                print("Ученик не найден!")

        elif choice == '3':
            name = input("\nВведите имя ученика для удаления: ")
            db.remove_student(name)
            print(f"Ученик {name} удален!")

        elif choice == '4':
            name = input("\nВведите имя ученика для удаления оценки: ")
            student = db.find_student(name)
            if student:
                print(f"Оценки ученика {name}: {student.grades}")
                index = int(input("Введите индекс оценки для удаления (начиная с 0): "))
                student.remove_grades(index)
                print(f"Оценка по индексу {index} удалена.")
            else:
                print("Ученик не найден!")

        elif choice == '5':
            name = input("\nВведите имя ученика для изменения оценки: ")
            student = db.find_student(name)
            if student:
                print(f"Оценки ученика {name}: {student.grades}")
                index = int(input("Введите индекс оценки для изменения: "))
                new_grade = int(input("Введите новую оценку: "))
                student.update_grade(index, new_grade)
                print(f"Оценка по индексу {index} изменена на {new_grade}.")
            else:
                print("Ученик не найден!")

        elif choice == '6':
            name = input("\nВведите имя ученика для подсчета итоговой оценки: ")
            student = db.find_student(name)
            if student:
                print(f"Итоговая оценка ученика {name}: {student.calculate_final_grade():.2f}")
            else:
                print("Ученик не найден!")

        elif choice == '7':
            print("\nИтоговые оценки всех учеников:")
            for student in db.students:
                print(f"{student.name}: {student.calculate_final_grade():.2f}")

        elif choice == '8':
            db.save_to_file(file_path)
            print("Изменения сохранены. Выход из программы.")
            break

        elif choice == '9':
            print("Выход без сохранения.")
            break

        else:
            print("Некорректный выбор! Пожалуйста, выберите опцию от 1 до 9.")

if __name__ == "__main__":
    main()
