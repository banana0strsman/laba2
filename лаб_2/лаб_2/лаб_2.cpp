#include <iostream>
#include <queue>
#include <string>
#include <functional>

struct Hospital {
	int total_beds;
	int free_beds;
	std::function<double()> distance;
};

struct Patient {
	std::string name;
	bool admitted;
};

std::queue<Hospital> hospitals;
std::queue<Patient> patients;

void admit_patient(Patient patient) {
	if (hospitals.empty()) {
		std::cout << "Нет свободных больниц для пациента " << patient.name << std::endl;
		return;
	}
	Hospital hospital = hospitals.front();
	hospitals.pop();
	hospital.free_beds--;
	if (hospital.free_beds > 0) {
		hospitals.push(hospital);
	}
	patient.admitted = true;
	patients.push(patient);
	std::cout << "Пациент " << patient.name << " принят в больницу на расстоянии " << hospital.distance() << std::endl;
}

void discharge_patient(Patient patient) {
	if (patients.empty()) {
		std::cout << "Нет пациентов для выписки" << std::endl;
		return;
	}
	Hospital hospital = hospitals.front();
	hospitals.pop();
	hospital.free_beds++;
	hospitals.push(hospital);
	patient.admitted = false;
	patients.pop();
	std::cout << "Пациент " << patient.name << " выписан из больницы" << std::endl;
}

void update_hospitals() {
	int total_free_beds = 0;
	std::queue<Hospital> temp_queue;
	while (!hospitals.empty()) {
		Hospital hospital = hospitals.front();
		hospitals.pop();
		total_free_beds += hospital.free_beds;
		temp_queue.push(hospital);
		std::cout << "Больница на расстоянии " << hospital.distance() << " имеет " << hospital.free_beds << " свободных мест" << std::endl;
	}
	hospitals = temp_queue;
	std::cout << "Всего свободных мест: " << total_free_beds << std::endl;
}

int main() {
	setlocale(0, "ru");
	hospitals.push({ 100, 50, []() {return 10.5; } });
	hospitals.push({ 200, 100, []() {return 5.2; } });

	patients.push({ "Иванов", false });

	update_hospitals();

	admit_patient(patients.front());

	update_hospitals();

	discharge_patient(patients.front());

	update_hospitals();

	return 0;
}