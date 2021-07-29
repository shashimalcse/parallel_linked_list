from subprocess import call, Popen, PIPE
import subprocess
import statistics

n_samples = 20
n_threads = 1

print ("Using {0} threads".format(n_threads))

"""
CASE 1
"""
print ("CASE 1========================")
print ("SERIAL-------")
exec_time_list_serial = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list", "1000", "10000", "0.99","0.005", "0.005"]))
    exec_time_list_serial.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_serial)/len(exec_time_list_serial))))
print ("Std: " + str(statistics.stdev(exec_time_list_serial)))

print ("ONE MUTEX FOR ENTIRE LIST-------")
exec_time_list_mutex = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list_mutex", str(n_threads), "1000", "10000", "0.99","0.005", "0.005"]))
    exec_time_list_mutex.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_mutex)/len(exec_time_list_mutex))))
print ("Std: " + str(statistics.stdev(exec_time_list_mutex)))

print ("READ-WRITE LOCK-------")
exec_time_list_rwlock = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list_read_write_lock", str(n_threads), "1000", "10000", "0.99","0.005", "0.005"]))
    exec_time_list_rwlock.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_rwlock)/len(exec_time_list_rwlock))))
print ("Std: " + str(statistics.stdev(exec_time_list_rwlock)))

"""
CASE 2
"""
print ("CASE 2========================")
print ("SERIAL-------")
exec_time_list_serial = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list", "1000", "10000", "0.9","0.05", "0.05"]))
    exec_time_list_serial.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_serial)/len(exec_time_list_serial))))
print ("Std: " + str(statistics.stdev(exec_time_list_serial)))

print ("ONE MUTEX FOR ENTIRE LIST-------")
exec_time_list_mutex = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list_mutex", str(n_threads), "1000", "10000", "0.9","0.05", "0.05"]))
    exec_time_list_mutex.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_mutex)/len(exec_time_list_mutex))))
print ("Std: " + str(statistics.stdev(exec_time_list_mutex)))

print ("READ-WRITE LOCK-------")
exec_time_list_rwlock = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list_read_write_lock", str(n_threads), "1000", "10000", "0.9","0.05", "0.05"]))
    exec_time_list_rwlock.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_rwlock)/len(exec_time_list_rwlock))))
print ("Std: " + str(statistics.stdev(exec_time_list_rwlock)))

"""
CASE 3
"""
print ("CASE 3========================")
print ("SERIAL-------")
exec_time_list_serial = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list", "1000", "10000", "0.5","0.25", "0.25"]))
    exec_time_list_serial.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_serial)/len(exec_time_list_serial))))
print ("Std: " + str(statistics.stdev(exec_time_list_serial)))

print ("ONE MUTEX FOR ENTIRE LIST-------")
exec_time_list_mutex = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list_mutex", str(n_threads), "1000", "10000", "0.5","0.25", "0.25"]))
    exec_time_list_mutex.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_mutex)/len(exec_time_list_mutex))))
print ("Std: " + str(statistics.stdev(exec_time_list_mutex)))

print ("READ-WRITE LOCK-------")
exec_time_list_rwlock = []
for i in range(n_samples):
    exec_time = float(subprocess.check_output(["./linked_list_read_write_lock", str(n_threads), "1000", "10000", "0.5","0.25", "0.25"]))
    exec_time_list_rwlock.append(exec_time)
print ("Avg: " + str((sum(exec_time_list_rwlock)/len(exec_time_list_rwlock))))
print ("Std: " + str(statistics.stdev(exec_time_list_rwlock)))
